/* fseeko/ftello with 64-bit offsets outside Windows, for images over 2 GB. */
#if !defined(_WIN32)
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif
#endif

#include "disc_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ISO 9660 layout (ECMA-119). */
#define ISO_PVD_LSN 16u
#define ISO_PVD_ROOT_RECORD 156u
#define ISO_RECORD_MIN 34u
#define ISO_FLAG_DIRECTORY 0x02u
#define ISO_MAX_DEPTH 8
/* Directories larger than this are treated as malformed. */
#define ISO_MAX_DIRECTORY_BYTES (16u * 1024u * 1024u)
#define ISO_MAX_NAME 255u

#define RAW_SECTOR_SIZE 2352u

struct DiscImage {
    FILE *file;
    const unsigned char *memory;
    uint64_t image_size;
    uint32_t raw_sector_size; /* bytes per sector in the image */
    uint32_t data_offset;     /* user data offset within a raw sector */
    uint32_t sector_count;
    DiscFile root;
};

static uint32_t read_le32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static DiscStatus raw_read(DiscImage *disc, uint64_t offset, void *buffer, size_t size)
{
    if (offset > disc->image_size || size > disc->image_size - offset)
        return DISC_ERR_RANGE;
    if (disc->memory) {
        memcpy(buffer, disc->memory + offset, size);
        return DISC_OK;
    }
#ifdef _WIN32
    if (_fseeki64(disc->file, (long long)offset, SEEK_SET) != 0)
        return DISC_ERR_IO;
#else
    if (fseeko(disc->file, (off_t)offset, SEEK_SET) != 0)
        return DISC_ERR_IO;
#endif
    if (fread(buffer, 1, size, disc->file) != size)
        return DISC_ERR_IO;
    return DISC_OK;
}

DiscStatus disc_read_sectors(DiscImage *disc, uint32_t lsn, uint32_t count, void *buffer)
{
    unsigned char *out = buffer;
    if (!disc || (!buffer && count))
        return DISC_ERR_ARGUMENT;
    if (lsn > disc->sector_count || count > disc->sector_count - lsn)
        return DISC_ERR_RANGE;
    if (disc->raw_sector_size == DISC_SECTOR_SIZE)
        return raw_read(disc, (uint64_t)lsn * DISC_SECTOR_SIZE, out, (size_t)count * DISC_SECTOR_SIZE);
    for (uint32_t i = 0; i < count; i++) {
        uint64_t at = (uint64_t)(lsn + i) * disc->raw_sector_size + disc->data_offset;
        DiscStatus status = raw_read(disc, at, out + (size_t)i * DISC_SECTOR_SIZE, DISC_SECTOR_SIZE);
        if (status != DISC_OK)
            return status;
    }
    return DISC_OK;
}

DiscStatus disc_read(DiscImage *disc, uint64_t offset, void *buffer, size_t size)
{
    unsigned char *out = buffer;
    uint64_t end = (uint64_t)disc_sector_count(disc) * DISC_SECTOR_SIZE;
    if (!disc || (!buffer && size))
        return DISC_ERR_ARGUMENT;
    if (offset > end || size > end - offset)
        return DISC_ERR_RANGE;
    if (disc->raw_sector_size == DISC_SECTOR_SIZE)
        return raw_read(disc, offset, out, size);
    while (size) {
        uint32_t lsn = (uint32_t)(offset / DISC_SECTOR_SIZE);
        uint32_t within = (uint32_t)(offset % DISC_SECTOR_SIZE);
        size_t chunk = DISC_SECTOR_SIZE - within;
        if (chunk > size)
            chunk = size;
        DiscStatus status = raw_read(disc, (uint64_t)lsn * disc->raw_sector_size + disc->data_offset + within, out, chunk);
        if (status != DISC_OK)
            return status;
        out += chunk;
        offset += chunk;
        size -= chunk;
    }
    return DISC_OK;
}

uint32_t disc_sector_count(const DiscImage *disc)
{
    return disc ? disc->sector_count : 0;
}

uint32_t disc_raw_sector_size(const DiscImage *disc)
{
    return disc ? disc->raw_sector_size : 0;
}

/* Looks for the Primary Volume Descriptor with one sector layout. */
static int probe_layout(DiscImage *disc, uint32_t raw_sector_size, uint32_t data_offset)
{
    unsigned char header[6];
    disc->raw_sector_size = raw_sector_size;
    disc->data_offset = data_offset;
    if (raw_read(disc, (uint64_t)ISO_PVD_LSN * raw_sector_size + data_offset, header, sizeof header) != DISC_OK)
        return 0;
    return header[0] == 1 && memcmp(header + 1, "CD001", 5) == 0;
}

static DiscStatus finish_open(DiscImage *disc, DiscImage **out)
{
    unsigned char pvd[DISC_SECTOR_SIZE];
    const unsigned char *root;
    DiscStatus status;

    if (!probe_layout(disc, DISC_SECTOR_SIZE, 0) && !probe_layout(disc, RAW_SECTOR_SIZE, 16) &&
        !probe_layout(disc, RAW_SECTOR_SIZE, 24)) {
        disc_close(disc);
        return DISC_ERR_FORMAT;
    }
    {
        uint64_t sectors = disc->image_size / disc->raw_sector_size;
        /* A last sector without its full user data is not readable. */
        if (disc->image_size % disc->raw_sector_size >= disc->data_offset + DISC_SECTOR_SIZE)
            sectors++;
        disc->sector_count = sectors > UINT32_MAX ? UINT32_MAX : (uint32_t)sectors;
    }
    status = disc_read_sectors(disc, ISO_PVD_LSN, 1, pvd);
    if (status != DISC_OK) {
        disc_close(disc);
        return status;
    }
    root = pvd + ISO_PVD_ROOT_RECORD;
    if (root[0] < ISO_RECORD_MIN || !(root[25] & ISO_FLAG_DIRECTORY)) {
        disc_close(disc);
        return DISC_ERR_FORMAT;
    }
    disc->root.lsn = read_le32(root + 2);
    disc->root.size = read_le32(root + 10);
    *out = disc;
    return DISC_OK;
}

DiscStatus disc_open(const char *path, DiscImage **out)
{
    DiscImage *disc;
    if (!path || !out)
        return DISC_ERR_ARGUMENT;
    *out = NULL;
    disc = calloc(1, sizeof *disc);
    if (!disc)
        return DISC_ERR_NOMEM;
    disc->file = fopen(path, "rb");
    if (!disc->file) {
        free(disc);
        return DISC_ERR_IO;
    }
#ifdef _WIN32
    if (_fseeki64(disc->file, 0, SEEK_END) != 0) {
        disc_close(disc);
        return DISC_ERR_IO;
    }
    {
        long long size = _ftelli64(disc->file);
        if (size < 0) {
            disc_close(disc);
            return DISC_ERR_IO;
        }
        disc->image_size = (uint64_t)size;
    }
#else
    if (fseeko(disc->file, 0, SEEK_END) != 0) {
        disc_close(disc);
        return DISC_ERR_IO;
    }
    {
        off_t size = ftello(disc->file);
        if (size < 0) {
            disc_close(disc);
            return DISC_ERR_IO;
        }
        disc->image_size = (uint64_t)size;
    }
#endif
    return finish_open(disc, out);
}

DiscStatus disc_open_memory(const void *data, size_t size, DiscImage **out)
{
    DiscImage *disc;
    if (!data || !out)
        return DISC_ERR_ARGUMENT;
    *out = NULL;
    disc = calloc(1, sizeof *disc);
    if (!disc)
        return DISC_ERR_NOMEM;
    disc->memory = data;
    disc->image_size = size;
    return finish_open(disc, out);
}

void disc_close(DiscImage *disc)
{
    if (!disc)
        return;
    if (disc->file)
        fclose(disc->file);
    free(disc);
}

static char ascii_upper(char c)
{
    return (c >= 'a' && c <= 'z') ? (char)(c - 'a' + 'A') : c;
}

/* Copies an ISO 9660 identifier without its ";version" suffix or the
 * trailing '.' of a name without an extension. */
static void normalize_name(const char *name, size_t length, char out[ISO_MAX_NAME + 1])
{
    size_t n = 0;
    while (n < length && n < ISO_MAX_NAME && name[n] != ';') {
        out[n] = name[n];
        n++;
    }
    if (n > 0 && out[n - 1] == '.')
        n--;
    out[n] = '\0';
}

static int names_equal(const char *a, const char *b)
{
    while (*a && *b) {
        if (ascii_upper(*a) != ascii_upper(*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

typedef int (*RecordFn)(void *context, const char *name, const DiscFile *file, int is_directory);

/* Walks the records of one directory extent. */
static DiscStatus walk_directory(DiscImage *disc, const DiscFile *dir, RecordFn fn, void *context)
{
    unsigned char *data;
    uint32_t sectors;
    DiscStatus status;

    if (dir->size > ISO_MAX_DIRECTORY_BYTES)
        return DISC_ERR_FORMAT;
    sectors = (dir->size + DISC_SECTOR_SIZE - 1) / DISC_SECTOR_SIZE;
    data = malloc((size_t)sectors * DISC_SECTOR_SIZE + 1);
    if (!data)
        return DISC_ERR_NOMEM;
    status = disc_read_sectors(disc, dir->lsn, sectors, data);
    if (status == DISC_ERR_RANGE)
        status = DISC_ERR_FORMAT;
    if (status != DISC_OK) {
        free(data);
        return status;
    }

    for (uint32_t pos = 0; pos < dir->size;) {
        uint32_t sector_end = (pos / DISC_SECTOR_SIZE + 1) * DISC_SECTOR_SIZE;
        uint32_t length = data[pos];
        uint32_t name_length;
        DiscFile file;
        char name[ISO_MAX_NAME + 1];

        if (length == 0) {
            /* Records never cross a sector; the rest of this one is padding. */
            pos = sector_end;
            continue;
        }
        if (length < ISO_RECORD_MIN || pos + length > sector_end || pos + length > dir->size) {
            free(data);
            return DISC_ERR_FORMAT;
        }
        name_length = data[pos + 32];
        if (33 + name_length > length) {
            free(data);
            return DISC_ERR_FORMAT;
        }
        file.lsn = read_le32(data + pos + 2);
        file.size = read_le32(data + pos + 10);
        /* Identifiers 0 and 1 are "." and "..". */
        if (!(name_length == 1 && data[pos + 33] <= 1)) {
            normalize_name((const char *)data + pos + 33, name_length, name);
            if (fn(context, name, &file, (data[pos + 25] & ISO_FLAG_DIRECTORY) != 0)) {
                free(data);
                return DISC_OK;
            }
        }
        pos += length;
    }
    free(data);
    return DISC_OK;
}

typedef struct FindContext {
    const char *want;
    DiscFile file;
    int is_directory;
    int found;
} FindContext;

static int find_record(void *context, const char *name, const DiscFile *file, int is_directory)
{
    FindContext *find = context;
    if (!names_equal(name, find->want))
        return 0;
    find->file = *file;
    find->is_directory = is_directory;
    find->found = 1;
    return 1;
}

/* Resolves `path` to a directory record or file record. */
static DiscStatus resolve(DiscImage *disc, const char *path, DiscFile *out, int *is_directory)
{
    DiscFile current = disc->root;
    int current_is_directory = 1;
    int depth = 0;
    const char *p = path;

    for (;;) {
        char component[ISO_MAX_NAME + 1];
        size_t n = 0;
        FindContext find;
        DiscStatus status;

        while (*p == '\\' || *p == '/')
            p++;
        if (*p == '\0')
            break;
        if (!current_is_directory)
            return DISC_ERR_NOT_FOUND;
        if (++depth > ISO_MAX_DEPTH)
            return DISC_ERR_NOT_FOUND;
        while (*p && *p != '\\' && *p != '/') {
            if (n == ISO_MAX_NAME)
                return DISC_ERR_NOT_FOUND;
            component[n++] = *p++;
        }
        normalize_name(component, n, component);

        memset(&find, 0, sizeof find);
        find.want = component;
        status = walk_directory(disc, &current, find_record, &find);
        if (status != DISC_OK)
            return status;
        if (!find.found)
            return DISC_ERR_NOT_FOUND;
        current = find.file;
        current_is_directory = find.is_directory;
    }
    *out = current;
    *is_directory = current_is_directory;
    return DISC_OK;
}

DiscStatus disc_find_file(DiscImage *disc, const char *path, DiscFile *out)
{
    DiscFile file;
    int is_directory;
    DiscStatus status;

    if (!disc || !path || !out)
        return DISC_ERR_ARGUMENT;
    status = resolve(disc, path, &file, &is_directory);
    if (status != DISC_OK)
        return status;
    if (is_directory)
        return DISC_ERR_NOT_FOUND;
    *out = file;
    return DISC_OK;
}

DiscStatus disc_list_directory(DiscImage *disc, const char *path, DiscDirFn fn, void *context)
{
    DiscFile dir;
    int is_directory;
    DiscStatus status;

    if (!disc || !path || !fn)
        return DISC_ERR_ARGUMENT;
    status = resolve(disc, path, &dir, &is_directory);
    if (status != DISC_OK)
        return status;
    if (!is_directory)
        return DISC_ERR_NOT_FOUND;
    return walk_directory(disc, &dir, fn, context);
}

const char *disc_status_string(DiscStatus status)
{
    switch (status) {
    case DISC_OK:
        return "ok";
    case DISC_ERR_IO:
        return "the disc image could not be read";
    case DISC_ERR_FORMAT:
        return "not an ISO 9660 disc image, or a malformed one";
    case DISC_ERR_NOT_FOUND:
        return "file not found on the disc";
    case DISC_ERR_RANGE:
        return "read past the end of the disc image";
    case DISC_ERR_NOMEM:
        return "out of memory";
    case DISC_ERR_ARGUMENT:
        return "invalid argument";
    }
    return "unknown error";
}
