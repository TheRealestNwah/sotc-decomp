#include "synthetic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECTOR 2048u
#define ROOT_LSN 18u
#define MAX_DIRS 8

void bytes_put(Bytes *b, const void *data, size_t size)
{
    if (b->size + size > b->capacity) {
        size_t capacity = b->capacity ? b->capacity : 256;
        while (capacity < b->size + size)
            capacity *= 2;
        b->data = realloc(b->data, capacity);
        if (!b->data) {
            fprintf(stderr, "out of memory\n");
            exit(2);
        }
        b->capacity = capacity;
    }
    if (size)
        memcpy(b->data + b->size, data, size);
    b->size += size;
}

void bytes_put_u16(Bytes *b, uint16_t value)
{
    unsigned char p[2] = {(unsigned char)value, (unsigned char)(value >> 8)};
    bytes_put(b, p, sizeof p);
}

void bytes_put_u32(Bytes *b, uint32_t value)
{
    unsigned char p[4] = {(unsigned char)value, (unsigned char)(value >> 8), (unsigned char)(value >> 16),
        (unsigned char)(value >> 24)};
    bytes_put(b, p, sizeof p);
}

void bytes_put_zeros(Bytes *b, size_t size)
{
    static const unsigned char zeros[256];
    while (size) {
        size_t chunk = size < sizeof zeros ? size : sizeof zeros;
        bytes_put(b, zeros, chunk);
        size -= chunk;
    }
}

void bytes_free(Bytes *b)
{
    free(b->data);
    b->data = NULL;
    b->size = b->capacity = 0;
}

static void put_both32(unsigned char *p, uint32_t v)
{
    for (int i = 0; i < 4; i++) {
        p[i] = (unsigned char)(v >> (8 * i));
        p[7 - i] = (unsigned char)(v >> (8 * i));
    }
}

static size_t record_length(size_t name_length)
{
    size_t length = 33 + name_length;
    return length + (length & 1);
}

/* Writes one directory record; returns its length. */
static size_t write_record(unsigned char *p, uint32_t lsn, uint32_t size, int directory, const char *name,
    size_t name_length)
{
    size_t length = record_length(name_length);
    memset(p, 0, length);
    p[0] = (unsigned char)length;
    put_both32(p + 2, lsn);
    put_both32(p + 10, size);
    p[25] = directory ? 2 : 0;
    p[28] = 1; /* volume sequence number */
    p[32] = (unsigned char)name_length;
    memcpy(p + 33, name, name_length);
    return length;
}

typedef struct Record {
    const char *name;
    size_t name_length;
    uint32_t lsn;
    uint32_t size;
    int directory;
} Record;

typedef struct Dir {
    const char *name;
    Record records[512];
    size_t count;
    uint32_t lsn;
    uint32_t size; /* bytes, a whole number of sectors */
} Dir;

static void add_record(Dir *d, const char *name, size_t name_length, int directory)
{
    Record *r = &d->records[d->count++];
    r->name = name;
    r->name_length = name_length;
    r->directory = directory;
}

/* Lays records into sectors without letting one cross a boundary. */
static uint32_t layout_size(const Dir *d)
{
    size_t pos = 0;
    for (size_t i = 0; i < d->count; i++) {
        size_t length = record_length(d->records[i].name_length);
        if (pos / SECTOR != (pos + length - 1) / SECTOR)
            pos = (pos / SECTOR + 1) * SECTOR;
        pos += length;
    }
    return (uint32_t)((pos + SECTOR - 1) / SECTOR * SECTOR);
}

static void write_dir(unsigned char *image, const Dir *d)
{
    unsigned char *base = image + (size_t)d->lsn * SECTOR;
    size_t pos = 0;
    for (size_t i = 0; i < d->count; i++) {
        const Record *r = &d->records[i];
        size_t length = record_length(r->name_length);
        if (pos / SECTOR != (pos + length - 1) / SECTOR)
            pos = (pos / SECTOR + 1) * SECTOR;
        pos += write_record(base + pos, r->lsn, r->size, r->directory, r->name, r->name_length);
    }
}

unsigned char *iso_build(const IsoEntry *entries, size_t count, size_t *out_size)
{
    static Dir dirs[MAX_DIRS + 1];
    size_t dir_count = 1;
    uint32_t next;
    size_t sectors;
    unsigned char *image;
    unsigned char *pvd;
    static const char dot[1] = {0}, dotdot[1] = {1};

    memset(dirs, 0, sizeof dirs);
    add_record(&dirs[0], dot, 1, 1);
    add_record(&dirs[0], dotdot, 1, 1);
    for (size_t i = 0; i < count; i++) {
        size_t d = 0;
        if (!entries[i].dir)
            continue;
        for (d = 1; d < dir_count; d++)
            if (strcmp(dirs[d].name, entries[i].dir) == 0)
                break;
        if (d == dir_count) {
            dirs[d].name = entries[i].dir;
            add_record(&dirs[d], dot, 1, 1);
            add_record(&dirs[d], dotdot, 1, 1);
            add_record(&dirs[0], entries[i].dir, strlen(entries[i].dir), 1);
            dir_count++;
        }
    }
    for (size_t i = 0; i < count; i++) {
        size_t d = 0;
        if (entries[i].dir)
            for (d = 1; strcmp(dirs[d].name, entries[i].dir) != 0; d++)
                ;
        add_record(&dirs[d], entries[i].name, strlen(entries[i].name), 0);
    }

    next = ROOT_LSN;
    for (size_t d = 0; d < dir_count; d++) {
        dirs[d].lsn = next;
        dirs[d].size = layout_size(&dirs[d]);
        next += dirs[d].size / SECTOR;
    }
    for (size_t d = 0; d < dir_count; d++) {
        /* "." is the directory itself, ".." its parent (the root's is itself). */
        dirs[d].records[0].lsn = dirs[d].lsn;
        dirs[d].records[0].size = dirs[d].size;
        dirs[d].records[1].lsn = dirs[0].lsn;
        dirs[d].records[1].size = dirs[0].size;
    }
    for (size_t d = 1; d < dir_count; d++) {
        for (size_t r = 2; r < dirs[0].count; r++)
            if (dirs[0].records[r].directory && dirs[0].records[r].name == dirs[d].name) {
                dirs[0].records[r].lsn = dirs[d].lsn;
                dirs[0].records[r].size = dirs[d].size;
            }
    }
    for (size_t i = 0; i < count; i++) {
        size_t d = 0;
        if (entries[i].dir)
            for (d = 1; strcmp(dirs[d].name, entries[i].dir) != 0; d++)
                ;
        for (size_t r = 2; r < dirs[d].count; r++)
            if (dirs[d].records[r].name == entries[i].name && !dirs[d].records[r].directory) {
                dirs[d].records[r].lsn = next;
                dirs[d].records[r].size = entries[i].size;
            }
        next += (entries[i].size + SECTOR - 1) / SECTOR;
    }

    sectors = next;
    image = calloc(sectors, SECTOR);
    if (!image) {
        fprintf(stderr, "out of memory\n");
        exit(2);
    }
    pvd = image + 16 * SECTOR;
    pvd[0] = 1;
    memcpy(pvd + 1, "CD001", 5);
    pvd[6] = 1;
    memset(pvd + 8, ' ', 32);
    memcpy(pvd + 40, "SYNTHETIC", 9);
    memset(pvd + 49, ' ', 23);
    put_both32(pvd + 80, (uint32_t)sectors);
    write_record(pvd + 156, dirs[0].lsn, dirs[0].size, 1, dot, 1);
    image[17 * SECTOR] = 255;
    memcpy(image + 17 * SECTOR + 1, "CD001", 5);
    image[17 * SECTOR + 6] = 1;

    for (size_t d = 0; d < dir_count; d++)
        write_dir(image, &dirs[d]);
    for (size_t i = 0; i < count; i++) {
        size_t d = 0;
        if (entries[i].dir)
            for (d = 1; strcmp(dirs[d].name, entries[i].dir) != 0; d++)
                ;
        for (size_t r = 2; r < dirs[d].count; r++)
            if (dirs[d].records[r].name == entries[i].name && !dirs[d].records[r].directory && entries[i].size)
                memcpy(image + (size_t)dirs[d].records[r].lsn * SECTOR, entries[i].data, entries[i].size);
    }
    *out_size = sectors * SECTOR;
    return image;
}

unsigned char *iso_to_raw(const unsigned char *image, size_t size, int mode, size_t *out_size)
{
    size_t sectors = size / SECTOR;
    unsigned char *raw = calloc(sectors, 2352);
    if (!raw) {
        fprintf(stderr, "out of memory\n");
        exit(2);
    }
    for (size_t i = 0; i < sectors; i++) {
        unsigned char *p = raw + i * 2352;
        size_t data = mode == 1 ? 16 : 24;
        p[0] = 0;
        memset(p + 1, 0xFF, 10);
        p[11] = 0;
        p[15] = (unsigned char)mode;
        memcpy(p + data, image + i * SECTOR, SECTOR);
    }
    *out_size = sectors * 2352;
    return raw;
}
