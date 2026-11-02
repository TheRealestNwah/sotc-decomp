/*
 * Builders for synthetic test data. Nothing here comes from the disc: the
 * images and archives are made up so that tests run without game files.
 */
#ifndef SOTC_PORT_TESTS_SYNTHETIC_H
#define SOTC_PORT_TESTS_SYNTHETIC_H

#include <stddef.h>
#include <stdint.h>

/* A growable byte buffer. */
typedef struct Bytes {
    unsigned char *data;
    size_t size;
    size_t capacity;
} Bytes;

void bytes_put(Bytes *b, const void *data, size_t size);
void bytes_put_u16(Bytes *b, uint16_t value);
void bytes_put_u32(Bytes *b, uint32_t value);
void bytes_put_zeros(Bytes *b, size_t size);
void bytes_free(Bytes *b);

/* One file of a synthetic ISO 9660 image. `dir` is NULL for the root or
 * the name of a directory directly under it. `name` is the identifier as
 * stored on the disc, such as "NICO.DAT;1". */
typedef struct IsoEntry {
    const char *dir;
    const char *name;
    const void *data;
    uint32_t size;
} IsoEntry;

/* Builds an image with 2048-byte sectors. Returns a malloc'd buffer. */
unsigned char *iso_build(const IsoEntry *entries, size_t count, size_t *out_size);

/* Converts a 2048-byte-sector image to raw 2352-byte sectors in Mode 1
 * (mode 1) or Mode 2 Form 1 (mode 2). Returns a malloc'd buffer. */
unsigned char *iso_to_raw(const unsigned char *image, size_t size, int mode, size_t *out_size);

#endif
