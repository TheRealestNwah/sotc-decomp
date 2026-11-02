/*
 * NICO.DAT archive parser for the Native port.
 *
 * NICO.DAT holds almost all of the game's assets. Its header is a table of
 * contents that MANAGER's sheetFs code reads at boot (func_000DFEB0, called
 * from sheetFsInit); the layout is documented in docs/nicodat.md. This
 * parser reads that header into memory and answers the same lookups the
 * sheetFs* functions do. Asset contents are not interpreted.
 *
 * Every sector number in the archive counts from the start of NICO.DAT,
 * like the argument to iosCdStStart.
 */
#ifndef SOTC_PORT_NICODAT_H
#define SOTC_PORT_NICODAT_H

#include <stddef.h>
#include <stdint.h>

#include "disc_image.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NICO_DAT_PATH "\\NICO.DAT;1"

/* Bit 15 of a segment index entry selects the per-language table. */
#define NICO_INDEX_LOCALIZED 0x8000u

typedef enum NicoStatus {
    NICO_OK = 0,
    NICO_ERR_READ,      /* the read callback failed */
    NICO_ERR_TRUNCATED, /* the header runs past the end of the archive */
    NICO_ERR_FORMAT,    /* a count or name that cannot be right */
    NICO_ERR_NOT_FOUND,
    NICO_ERR_RANGE, /* an index outside its table */
    NICO_ERR_NOMEM,
    NICO_ERR_ARGUMENT
} NicoStatus;

/* A run of sectors in the archive. `size` is the second word of every
 * table entry; sheetFsGetDirectFileSize returns it as a file size. */
typedef struct NicoRecord {
    uint32_t sector;
    uint32_t size;
} NicoRecord;

/* A named group of files loaded by index (sheetFsLoadSegmentIndex,
 * sheetFsLoadStageTex), such as "stagetexseg_def". */
typedef struct NicoSegmentType {
    char *name;
    uint32_t index_count;
    uint16_t *index; /* an entry into `files`, or with bit 15 into `localized` */
    uint32_t file_count;
    NicoRecord *files;
    uint32_t localized_count;
    NicoRecord *localized; /* one run of entries per language */
} NicoSegmentType;

/* The two tables (variant 0 and 1) of one data type of a map. */
typedef struct NicoMapTable {
    uint32_t count;
    NicoRecord *variant[2];
} NicoMapTable;

/* Three words per entry; the third is a texture segment index
 * (sheetFsGetStageTexSegIndex). The first two are not yet known. */
typedef struct NicoTexSeg {
    uint32_t word[3];
} NicoTexSeg;

/* A world map (sheetFsLoadMap), with its file tables indexed by the
 * game's data type (0, 1 or 2) and variant (0 or 1). */
typedef struct NicoMap {
    char *name;
    NicoMapTable data_type[3];
    uint32_t tex_seg_count;
    NicoTexSeg *tex_segs;
} NicoMap;

/* A named block of data stored in the header itself (sheetFsSrhSpecialFs). */
typedef struct NicoSpecialFile {
    char *name;
    uint32_t value; /* meaning not yet known */
    uint32_t data_size;
    unsigned char *data;
} NicoSpecialFile;

typedef struct NicoArchive {
    NicoRecord boot; /* sheetFsLoadBootData */
    NicoRecord root; /* sheetFsLoadRootSegment */
    uint32_t segment_type_count;
    NicoSegmentType *segment_types;
    uint32_t map_count;
    NicoMap *maps;
    uint32_t adpcm_count;
    NicoRecord *adpcm; /* sheetFsLoadAdpcmInt */
    uint32_t direct_count;
    NicoRecord *direct; /* sheetFsLoadDirectFile, sheetFsGetDirectFileSize */
    uint32_t special_count;
    NicoSpecialFile *special;
    uint64_t header_size; /* bytes the header occupies */
} NicoArchive;

/* Reads `size` bytes at byte `offset` of the archive; returns 0 on success. */
typedef int (*NicoReadFn)(void *context, uint64_t offset, void *buffer, size_t size);

/* Parses the header of an archive of `archive_size` bytes. */
NicoStatus nico_parse(NicoReadFn read, void *context, uint64_t archive_size, NicoArchive **out);

/* Parses a header held in memory. */
NicoStatus nico_parse_memory(const void *data, size_t size, NicoArchive **out);

/* Finds NICO.DAT on a disc and parses its header. `file` (optional)
 * receives its location, needed by nico_disc_offset. */
NicoStatus nico_open_disc(DiscImage *disc, NicoArchive **out, DiscFile *file);

void nico_free(NicoArchive *archive);

const NicoSegmentType *nico_find_segment_type(const NicoArchive *archive, const char *name);

/* Resolves entry `index` of a segment type, as sheetFsLoadSegmentIndex
 * does. `language` is the game's 1-based sheetFsLanguageCode; it only
 * matters for localized entries. */
NicoStatus nico_segment_record(const NicoSegmentType *type, uint32_t index, uint32_t language, NicoRecord *out);

const NicoMap *nico_find_map(const NicoArchive *archive, const char *name);

/* Resolves entry `index` of a map table, as sheetFsLoadMap does. */
NicoStatus nico_map_record(const NicoMap *map, uint32_t data_type, uint32_t variant, uint32_t index, NicoRecord *out);

const NicoSpecialFile *nico_find_special(const NicoArchive *archive, const char *name);

/* Byte offset of a record within the archive. */
uint64_t nico_record_offset(const NicoRecord *record);

/* Byte offset of a record on the disc, for disc_read. */
uint64_t nico_disc_offset(const DiscFile *archive_file, const NicoRecord *record);

const char *nico_status_string(NicoStatus status);

#ifdef __cplusplus
}
#endif

#endif
