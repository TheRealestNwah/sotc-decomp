/*
 * Disc image reader for the Native port.
 *
 * Reads the ISO 9660 file system of the owner's Disc image, the way the
 * Original finds files with sceCdSearchFile: a file is located by path and
 * comes back as a starting sector (LSN) and a size in bytes, and reads are
 * by sector. Nothing is extracted or cached (ADR 0008).
 *
 * Supported image layouts: 2048-byte user-data sectors (.iso) and raw
 * 2352-byte sectors (Mode 1, or Mode 2 Form 1). Only the first ISO 9660
 * volume is read; a dual-layer image's second volume is not.
 */
#ifndef SOTC_PORT_DISC_IMAGE_H
#define SOTC_PORT_DISC_IMAGE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DISC_SECTOR_SIZE 2048u

typedef enum DiscStatus {
    DISC_OK = 0,
    DISC_ERR_IO,        /* the image could not be opened or read */
    DISC_ERR_FORMAT,    /* not an ISO 9660 image, or a malformed structure */
    DISC_ERR_NOT_FOUND, /* no file or directory with that path */
    DISC_ERR_RANGE,     /* a read past the end of the image */
    DISC_ERR_NOMEM,
    DISC_ERR_ARGUMENT
} DiscStatus;

/* Where a file lives on the disc, like the SDK's sceCdlFILE. */
typedef struct DiscFile {
    uint32_t lsn;  /* first sector */
    uint32_t size; /* size in bytes */
} DiscFile;

typedef struct DiscImage DiscImage;

/* Opens an image file. The file stays open until disc_close. */
DiscStatus disc_open(const char *path, DiscImage **out);

/* Opens an image held in memory. The caller keeps `data` alive and
 * unchanged until disc_close. */
DiscStatus disc_open_memory(const void *data, size_t size, DiscImage **out);

void disc_close(DiscImage *disc);

/* Number of whole sectors in the image. */
uint32_t disc_sector_count(const DiscImage *disc);

/* Bytes per sector in the image file: 2048 or 2352. */
uint32_t disc_raw_sector_size(const DiscImage *disc);

/* Reads `count` 2048-byte sectors starting at `lsn` into `buffer`. */
DiscStatus disc_read_sectors(DiscImage *disc, uint32_t lsn, uint32_t count, void *buffer);

/* Reads `size` bytes of user data starting at byte `offset`, where byte
 * offset N is byte N % 2048 of sector N / 2048. */
DiscStatus disc_read(DiscImage *disc, uint64_t offset, void *buffer, size_t size);

/* Finds a file by path. Path components are separated by '\' or '/', a
 * leading separator is optional, names compare case-insensitively, and a
 * ";1" version suffix is optional: "\NICO.DAT;1" and "nico.dat" find the
 * same file. Directories are not returned. */
DiscStatus disc_find_file(DiscImage *disc, const char *path, DiscFile *out);

/* Calls `fn` for each entry of the directory at `path` ("" or "\" for the
 * root), skipping "." and "..". `name` has its version suffix removed.
 * Stops early, returning DISC_OK, when `fn` returns nonzero. */
typedef int (*DiscDirFn)(void *context, const char *name, const DiscFile *file, int is_directory);
DiscStatus disc_list_directory(DiscImage *disc, const char *path, DiscDirFn fn, void *context);

const char *disc_status_string(DiscStatus status);

#ifdef __cplusplus
}
#endif

#endif
