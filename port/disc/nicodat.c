#include "nicodat.h"

#include <stdlib.h>
#include <string.h>

#define STREAM_BUFFER_SIZE (64u * 1024u)

/* A sequential reader over the header, like iosCdStRead on a stream
 * started at sector 0 of the archive. */
typedef struct Stream {
    NicoReadFn read;
    void *context;
    uint64_t size;
    uint64_t pos;
    uint64_t buffer_start;
    size_t buffer_length;
    unsigned char buffer[STREAM_BUFFER_SIZE];
} Stream;

static uint64_t remaining(const Stream *s)
{
    return s->size - s->pos;
}

static NicoStatus stream_read(Stream *s, void *out, size_t size)
{
    unsigned char *dst = out;
    if (size > remaining(s))
        return NICO_ERR_TRUNCATED;
    while (size) {
        size_t chunk;
        if (s->pos < s->buffer_start || s->pos >= s->buffer_start + s->buffer_length) {
            uint64_t left = remaining(s);
            s->buffer_start = s->pos;
            s->buffer_length = left < STREAM_BUFFER_SIZE ? (size_t)left : STREAM_BUFFER_SIZE;
            if (s->read(s->context, s->buffer_start, s->buffer, s->buffer_length) != 0) {
                s->buffer_length = 0;
                return NICO_ERR_READ;
            }
        }
        chunk = (size_t)(s->buffer_start + s->buffer_length - s->pos);
        if (chunk > size)
            chunk = size;
        memcpy(dst, s->buffer + (s->pos - s->buffer_start), chunk);
        dst += chunk;
        s->pos += chunk;
        size -= chunk;
    }
    return NICO_OK;
}

static uint32_t get_u32(const unsigned char *b)
{
    return (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

static NicoStatus read_u32(Stream *s, uint32_t *out)
{
    unsigned char b[4];
    NicoStatus status = stream_read(s, b, sizeof b);
    if (status == NICO_OK)
        *out = get_u32(b);
    return status;
}

/* Reads `count` elements of `element_size` bytes into a new allocation,
 * refusing counts the rest of the archive cannot hold. */
static NicoStatus read_block(Stream *s, uint32_t count, size_t element_size, unsigned char **out)
{
    uint64_t bytes = (uint64_t)count * element_size;
    NicoStatus status;
    *out = NULL;
    if (bytes > remaining(s))
        return NICO_ERR_TRUNCATED;
    if (bytes == 0)
        return NICO_OK;
    if (bytes > SIZE_MAX)
        return NICO_ERR_NOMEM;
    *out = malloc((size_t)bytes);
    if (!*out)
        return NICO_ERR_NOMEM;
    status = stream_read(s, *out, (size_t)bytes);
    if (status != NICO_OK) {
        free(*out);
        *out = NULL;
    }
    return status;
}

static NicoStatus read_record(Stream *s, NicoRecord *out)
{
    NicoStatus status = read_u32(s, &out->sector);
    if (status == NICO_OK)
        status = read_u32(s, &out->size);
    return status;
}

static NicoStatus read_records(Stream *s, uint32_t count, NicoRecord **out)
{
    unsigned char *raw;
    NicoStatus status = read_block(s, count, 8, &raw);
    *out = NULL;
    if (status != NICO_OK || count == 0)
        return status;
    /* Decode in place: NicoRecord is two uint32_t, the same size as on disc. */
    *out = (NicoRecord *)(void *)raw;
    for (uint32_t i = 0; i < count; i++) {
        const unsigned char *p = raw + (size_t)i * 8;
        uint32_t sector = (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
        uint32_t size = (uint32_t)p[4] | ((uint32_t)p[5] << 8) | ((uint32_t)p[6] << 16) | ((uint32_t)p[7] << 24);
        (*out)[i].sector = sector;
        (*out)[i].size = size;
    }
    return NICO_OK;
}

static char *copy_string(const char *src, size_t length)
{
    char *s = malloc(length + 1);
    if (s) {
        memcpy(s, src, length);
        s[length] = '\0';
    }
    return s;
}

/* Splits a block of NUL-terminated names into `count` copies. */
static NicoStatus split_names(const unsigned char *block, uint32_t block_size, uint32_t count, char **names,
    size_t stride)
{
    uint32_t pos = 0;
    for (uint32_t i = 0; i < count; i++) {
        const unsigned char *end;
        char **slot = (char **)(void *)((unsigned char *)names + (size_t)i * stride);
        if (pos >= block_size)
            return NICO_ERR_FORMAT;
        end = memchr(block + pos, '\0', block_size - pos);
        if (!end)
            return NICO_ERR_FORMAT;
        *slot = copy_string((const char *)block + pos, (size_t)(end - (block + pos)));
        if (!*slot)
            return NICO_ERR_NOMEM;
        pos = (uint32_t)(end - block) + 1;
    }
    return NICO_OK;
}

static NicoStatus read_names(Stream *s, uint32_t count, char **first_name, size_t stride)
{
    uint32_t block_size;
    unsigned char *block;
    NicoStatus status = read_u32(s, &block_size);
    if (status != NICO_OK)
        return status;
    status = read_block(s, block_size, 1, &block);
    if (status != NICO_OK)
        return status;
    status = split_names(block, block_size, count, first_name, stride);
    free(block);
    return status;
}

/* Allocates a zeroed array of `count` structs, refusing counts whose
 * smallest on-disc encoding (`min_bytes` each) cannot fit. */
static NicoStatus alloc_array(const Stream *s, uint32_t count, size_t element_size, uint64_t min_bytes, void **out)
{
    *out = NULL;
    if ((uint64_t)count * min_bytes > remaining(s))
        return NICO_ERR_TRUNCATED;
    if (count == 0)
        return NICO_OK;
    *out = calloc(count, element_size);
    return *out ? NICO_OK : NICO_ERR_NOMEM;
}

static NicoStatus parse_segment_types(Stream *s, NicoArchive *a)
{
    NicoStatus status = read_u32(s, &a->segment_type_count);
    if (status != NICO_OK)
        return status;
    /* The smallest entry is its three counts. */
    status = alloc_array(s, a->segment_type_count, sizeof *a->segment_types, 12, (void **)&a->segment_types);
    if (status != NICO_OK) {
        a->segment_type_count = 0;
        return status;
    }
    if (a->segment_type_count) {
        status = read_names(s, a->segment_type_count, &a->segment_types[0].name, sizeof *a->segment_types);
        if (status != NICO_OK)
            return status;
    }
    for (uint32_t i = 0; i < a->segment_type_count; i++) {
        NicoSegmentType *t = &a->segment_types[i];
        unsigned char *raw;
        status = read_u32(s, &t->index_count);
        if (status == NICO_OK)
            status = read_block(s, t->index_count, 2, &raw);
        if (status != NICO_OK) {
            t->index_count = 0;
            return status;
        }
        if (t->index_count) {
            t->index = (uint16_t *)(void *)raw;
            for (uint32_t j = 0; j < t->index_count; j++)
                t->index[j] = (uint16_t)(raw[j * 2] | (raw[j * 2 + 1] << 8));
        }
        status = read_u32(s, &t->file_count);
        if (status == NICO_OK)
            status = read_u32(s, &t->localized_count);
        if (status == NICO_OK)
            status = read_records(s, t->file_count, &t->files);
        if (status != NICO_OK) {
            t->file_count = t->localized_count = 0;
            return status;
        }
        status = read_records(s, t->localized_count, &t->localized);
        if (status != NICO_OK) {
            t->localized_count = 0;
            return status;
        }
    }
    return NICO_OK;
}

static NicoStatus parse_maps(Stream *s, NicoArchive *a)
{
    NicoStatus status = read_u32(s, &a->map_count);
    if (status != NICO_OK)
        return status;
    /* The smallest entry is a name length, three counts and a tex seg count. */
    status = alloc_array(s, a->map_count, sizeof *a->maps, 20, (void **)&a->maps);
    if (status != NICO_OK) {
        a->map_count = 0;
        return status;
    }
    for (uint32_t i = 0; i < a->map_count; i++) {
        NicoMap *m = &a->maps[i];
        uint32_t name_length;
        unsigned char *name;
        uint32_t counts[3];
        unsigned char *raw;

        status = read_u32(s, &name_length);
        if (status == NICO_OK)
            status = read_block(s, name_length, 1, &name);
        if (status != NICO_OK)
            return status;
        /* The game compares the name with strcmp, so it ends at the first
         * NUL; a name without one is taken whole. */
        {
            const unsigned char *end = name_length ? memchr(name, '\0', name_length) : NULL;
            size_t length = end ? (size_t)(end - name) : name_length;
            m->name = copy_string(name ? (const char *)name : "", length);
        }
        free(name);
        if (!m->name)
            return NICO_ERR_NOMEM;

        /* Stored as data types 2, 1, 0 (map record fields 0x10 to 0x24). */
        for (int k = 0; k < 3; k++) {
            status = read_u32(s, &counts[k]);
            if (status != NICO_OK)
                return status;
        }
        for (int k = 0; k < 3; k++) {
            NicoMapTable *table = &m->data_type[2 - k];
            for (int v = 0; v < 2; v++) {
                status = read_records(s, counts[k], &table->variant[v]);
                if (status != NICO_OK)
                    return status;
                table->count = counts[k];
            }
        }

        status = read_u32(s, &m->tex_seg_count);
        if (status == NICO_OK)
            status = read_block(s, m->tex_seg_count, 12, &raw);
        if (status != NICO_OK) {
            m->tex_seg_count = 0;
            return status;
        }
        if (m->tex_seg_count) {
            m->tex_segs = calloc(m->tex_seg_count, sizeof *m->tex_segs);
            if (!m->tex_segs) {
                free(raw);
                m->tex_seg_count = 0;
                return NICO_ERR_NOMEM;
            }
            for (uint32_t j = 0; j < m->tex_seg_count; j++) {
                const unsigned char *p = raw + (size_t)j * 12;
                m->tex_segs[j].x = (int32_t)get_u32(p);
                m->tex_segs[j].y = (int32_t)get_u32(p + 4);
                m->tex_segs[j].seg = get_u32(p + 8);
            }
            free(raw);
        }
    }
    return NICO_OK;
}

static NicoStatus parse_record_table(Stream *s, uint32_t *count, NicoRecord **records)
{
    NicoStatus status = read_u32(s, count);
    if (status == NICO_OK)
        status = read_records(s, *count, records);
    if (status != NICO_OK)
        *count = 0;
    return status;
}

static NicoStatus parse_special(Stream *s, NicoArchive *a)
{
    NicoStatus status = read_u32(s, &a->special_count);
    if (status != NICO_OK || a->special_count == 0)
        return status;
    /* Each entry needs at least a name byte, an entry count and a data size. */
    status = alloc_array(s, a->special_count, sizeof *a->special, 9, (void **)&a->special);
    if (status != NICO_OK) {
        a->special_count = 0;
        return status;
    }
    status = read_names(s, a->special_count, &a->special[0].name, sizeof *a->special);
    if (status != NICO_OK)
        return status;
    for (uint32_t i = 0; i < a->special_count; i++) {
        NicoSpecialFile *f = &a->special[i];
        status = read_u32(s, &f->entry_count);
        if (status == NICO_OK)
            status = read_u32(s, &f->data_size);
        if (status == NICO_OK)
            status = read_block(s, f->data_size, 1, &f->data);
        if (status != NICO_OK) {
            f->data_size = 0;
            return status;
        }
    }
    return NICO_OK;
}

NicoStatus nico_parse(NicoReadFn read, void *context, uint64_t archive_size, NicoArchive **out)
{
    Stream *s;
    NicoArchive *a;
    NicoStatus status;

    if (!read || !out)
        return NICO_ERR_ARGUMENT;
    *out = NULL;
    s = calloc(1, sizeof *s);
    a = calloc(1, sizeof *a);
    if (!s || !a) {
        free(s);
        free(a);
        return NICO_ERR_NOMEM;
    }
    s->read = read;
    s->context = context;
    s->size = archive_size;

    /* The order of func_000DFEB0's reads. */
    status = read_record(s, &a->boot);
    if (status == NICO_OK)
        status = read_record(s, &a->root);
    if (status == NICO_OK)
        status = parse_segment_types(s, a);
    if (status == NICO_OK)
        status = parse_maps(s, a);
    if (status == NICO_OK)
        status = parse_record_table(s, &a->adpcm_count, &a->adpcm);
    if (status == NICO_OK)
        status = parse_record_table(s, &a->direct_count, &a->direct);
    if (status == NICO_OK)
        status = parse_special(s, a);
    a->header_size = s->pos;
    free(s);
    if (status != NICO_OK) {
        nico_free(a);
        return status;
    }
    *out = a;
    return NICO_OK;
}

typedef struct MemoryContext {
    const unsigned char *data;
    size_t size;
} MemoryContext;

static int read_memory(void *context, uint64_t offset, void *buffer, size_t size)
{
    const MemoryContext *m = context;
    if (offset > m->size || size > m->size - offset)
        return -1;
    memcpy(buffer, m->data + offset, size);
    return 0;
}

NicoStatus nico_parse_memory(const void *data, size_t size, NicoArchive **out)
{
    MemoryContext m;
    if (!data && size)
        return NICO_ERR_ARGUMENT;
    m.data = data;
    m.size = size;
    return nico_parse(read_memory, &m, size, out);
}

typedef struct DiscContext {
    DiscImage *disc;
    uint64_t start;
} DiscContext;

static int read_disc(void *context, uint64_t offset, void *buffer, size_t size)
{
    const DiscContext *d = context;
    return disc_read(d->disc, d->start + offset, buffer, size) == DISC_OK ? 0 : -1;
}

NicoStatus nico_open_disc(DiscImage *disc, NicoArchive **out, DiscFile *file)
{
    DiscFile found;
    DiscContext d;

    if (!disc || !out)
        return NICO_ERR_ARGUMENT;
    *out = NULL;
    if (disc_find_file(disc, NICO_DAT_PATH, &found) != DISC_OK)
        return NICO_ERR_NOT_FOUND;
    if (file)
        *file = found;
    d.disc = disc;
    d.start = (uint64_t)found.lsn * DISC_SECTOR_SIZE;
    return nico_parse(read_disc, &d, found.size, out);
}

void nico_free(NicoArchive *a)
{
    if (!a)
        return;
    for (uint32_t i = 0; a->segment_types && i < a->segment_type_count; i++) {
        free(a->segment_types[i].name);
        free(a->segment_types[i].index);
        free(a->segment_types[i].files);
        free(a->segment_types[i].localized);
    }
    free(a->segment_types);
    for (uint32_t i = 0; a->maps && i < a->map_count; i++) {
        free(a->maps[i].name);
        for (int k = 0; k < 3; k++) {
            free(a->maps[i].data_type[k].variant[0]);
            free(a->maps[i].data_type[k].variant[1]);
        }
        free(a->maps[i].tex_segs);
    }
    free(a->maps);
    free(a->adpcm);
    free(a->direct);
    for (uint32_t i = 0; a->special && i < a->special_count; i++) {
        free(a->special[i].name);
        free(a->special[i].data);
    }
    free(a->special);
    free(a);
}

const NicoSegmentType *nico_find_segment_type(const NicoArchive *a, const char *name)
{
    if (!a || !name)
        return NULL;
    for (uint32_t i = 0; i < a->segment_type_count; i++)
        if (strcmp(a->segment_types[i].name, name) == 0)
            return &a->segment_types[i];
    return NULL;
}

NicoStatus nico_segment_record(const NicoSegmentType *t, uint32_t index, uint32_t language, NicoRecord *out)
{
    uint32_t entry;
    if (!t || !out)
        return NICO_ERR_ARGUMENT;
    if (index >= t->index_count)
        return NICO_ERR_RANGE;
    entry = t->index[index];
    if (!(entry & NICO_INDEX_LOCALIZED)) {
        if (entry >= t->file_count)
            return NICO_ERR_RANGE;
        *out = t->files[entry];
        return NICO_OK;
    }
    /* localized[(entry & 0x7FFF) + language - 1], as the game computes it. */
    if (language == 0)
        return NICO_ERR_ARGUMENT;
    entry = (entry & 0x7FFFu) + language - 1;
    if (entry >= t->localized_count)
        return NICO_ERR_RANGE;
    *out = t->localized[entry];
    return NICO_OK;
}

const NicoMap *nico_find_map(const NicoArchive *a, const char *name)
{
    if (!a || !name)
        return NULL;
    for (uint32_t i = 0; i < a->map_count; i++)
        if (strcmp(a->maps[i].name, name) == 0)
            return &a->maps[i];
    return NULL;
}

NicoStatus nico_map_record(const NicoMap *m, uint32_t data_type, uint32_t variant, uint32_t index, NicoRecord *out)
{
    const NicoMapTable *table;
    if (!m || !out || data_type > 2 || variant > 1)
        return NICO_ERR_ARGUMENT;
    table = &m->data_type[data_type];
    if (index >= table->count)
        return NICO_ERR_RANGE;
    *out = table->variant[variant][index];
    return NICO_OK;
}

const NicoSpecialFile *nico_find_special(const NicoArchive *a, const char *name)
{
    if (!a || !name)
        return NULL;
    for (uint32_t i = 0; i < a->special_count; i++)
        if (strcmp(a->special[i].name, name) == 0)
            return &a->special[i];
    return NULL;
}

NicoStatus nico_special_entry(const NicoSpecialFile *f, uint32_t index, NicoSpecialEntry *out)
{
    const unsigned char *p;
    if (!f || !out)
        return NICO_ERR_ARGUMENT;
    /* The game trusts entry_count; refuse entries the data doesn't hold. */
    if (index >= f->entry_count || index >= f->data_size / NICO_SPECIAL_ENTRY_SIZE)
        return NICO_ERR_RANGE;
    p = f->data + (size_t)index * NICO_SPECIAL_ENTRY_SIZE;
    memcpy(out->key, p, sizeof out->key);
    out->record.sector = get_u32(p + 8);
    out->record.size = get_u32(p + 12);
    return NICO_OK;
}

uint64_t nico_record_offset(const NicoRecord *record)
{
    return (uint64_t)record->sector * DISC_SECTOR_SIZE;
}

uint64_t nico_disc_offset(const DiscFile *archive_file, const NicoRecord *record)
{
    return ((uint64_t)archive_file->lsn + record->sector) * DISC_SECTOR_SIZE;
}

const char *nico_status_string(NicoStatus status)
{
    switch (status) {
    case NICO_OK:
        return "ok";
    case NICO_ERR_READ:
        return "the archive could not be read";
    case NICO_ERR_TRUNCATED:
        return "the archive header is truncated";
    case NICO_ERR_FORMAT:
        return "the archive header is malformed";
    case NICO_ERR_NOT_FOUND:
        return "NICO.DAT not found";
    case NICO_ERR_RANGE:
        return "index out of range";
    case NICO_ERR_NOMEM:
        return "out of memory";
    case NICO_ERR_ARGUMENT:
        return "invalid argument";
    }
    return "unknown error";
}
