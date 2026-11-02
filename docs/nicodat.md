# NICO.DAT

`NICO.DAT` is the archive on the disc that holds almost all of the game's assets
([ADR 0008](adr/0008-assets-from-the-owners-disc-image.md)). This page describes its
header as the Original reads it. The Native port's parser is
[`port/disc/nicodat.c`](../port/disc/nicodat.c).

Everything here comes from the Game modules' code, not from a dump of the file:
no `NICO.DAT` has been examined yet. Field meanings marked "not known" are
words the code reads and stores without using them in the functions below. Check
this page against the real file with `nicoinfo` once the owner has a Disc image.

## Finding it

KERNEL's `IosGetMergeDataFileName` returns `"\NICO.DAT;1"`. `iosCdStInit`
passes it to `sceCdSearchFile` and keeps the file's first sector, which
`iosCdStStart(lsn)` adds to every sector it is given. So every sector number in
the archive counts from the start of `NICO.DAT`, in 2048-byte sectors.
(`iosCdStInit` opens the name through `LoaderSysFOpen` instead when it starts
with `host0:`, a debug path.)

## Header

MANAGER's `sheetFsInit` calls `func_000DFEB0`, which starts a stream at sector 0
and reads the header field by field with `iosCdStRead`. The fields are packed
with no alignment padding. All integers are little-endian.

A *record* below is two `u32`s: a sector, then a size. `sheetFsGetDirectFileSize`
returns the second word of a direct-file record, so it is a size in bytes at
least there. `sheetFsLoadAdpcmInt` adds a sector offset to the first word of an
ADPCM record and reads from there with `sceCdReadIOPm` (through `iosIopRead`); it
doesn't use the second word, so that table's size unit is not settled.

| Field | Type | Stored in | Used by |
|---|---|---|---|
| boot | record | `B_001517C8` | `sheetFsLoadBootData` |
| root | record | `B_001517D0` | `sheetFsLoadRootSegment` |
| segment type count `N` | `u32` | `B_001517D8` | |
| names size | `u32` | | |
| names | `N` NUL-terminated strings | `B_001517DC` | |
| segment types | `N` × segment type | `B_001517E0` (0x1C bytes each) | `sheetFsLoadSegmentIndex`, `sheetFsLoadStageTex` |
| map count `M` | `u32` | `B_001517E8` | |
| maps | `M` × map | `B_001517E8 + 4` (0x28 bytes each), `B_001517C0` (0xC bytes each) | `sheetFsLoadMap`, `sheetFsGetStageTexSegIndex` |
| ADPCM count | `u32` | `B_001517F0` | |
| ADPCM | records | `B_001517F4` | `sheetFsLoadAdpcmInt` |
| direct file count | `u32` | `B_001517F8` | |
| direct files | records | `B_001517FC` | `sheetFsLoadDirectFile`, `sheetFsGetDirectFileSize` |
| special file count `S` | `u32` | `B_00151800` | |
| special files | only if `S` is not 0 | `B_00151800 + 4` (0xC bytes each) | `sheetFsSrhSpecialFs` |

### Segment type

The `i`th segment type takes the `i`th name from the names block.

| Field | Type |
|---|---|
| index count `n` | `u32` |
| index | `n` × `u16` |
| file count `f` | `u32` |
| localized count `l` | `u32` |
| files | `f` × record |
| localized | `l` × record |

`sheetFsLoadSegmentIndex(name, ..., index, ...)` looks up the type by name and
reads `index[index]`. Without bit 15 it selects `files[entry]`. With bit 15 it
selects `localized[(entry & 0x7FFF) + sheetFsLanguageCode - 1]`, so the language
code counts from 1 and each localized entry is a run of one record per language.
`sheetFsLoadStageTex` does the same for the type named `stagetexseg_def`.
After reading the header, `func_000DFEB0` also allocates a zeroed array of
`n` 8-byte entries for `stagetexseg_def` (`B_001517B8`, count in `B_001517BC`);
that is runtime state, not part of the file.

### Map

| Field | Type |
|---|---|
| name length | `u32` |
| name | that many bytes, compared with `strcmp` |
| count for data type 2 `c2` | `u32` |
| count for data type 1 `c1` | `u32` |
| count for data type 0 `c0` | `u32` |
| data type 2, variant 0 | `c2` × record |
| data type 2, variant 1 | `c2` × record |
| data type 1, variant 0 | `c1` × record |
| data type 1, variant 1 | `c1` × record |
| data type 0, variant 0 | `c0` × record |
| data type 0, variant 1 | `c0` × record |
| tex seg count `t` | `u32` |
| tex segs | `t` × three `u32`s |

`sheetFsLoadMap(name, dataType, variant, index, ...)` takes the table for
`dataType` (0 to 2) and `variant` (0 or 1) and starts the stream at that table's
record `index`. The tex seg entries go to a separate 12-byte-per-map table;
`sheetFsGetStageTexSegIndex` reads the third word of an entry of the first map's
table. The first two words are not known.

### Special file

The names block comes first, then one entry per name:

| Field | Type |
|---|---|
| names size | `u32` |
| names | `S` NUL-terminated strings |
| then for each special file: | |
| value | `u32`, not known |
| data size | `u32` |
| data | that many bytes |

## Not covered

- The sheetFs functions also have a "special fs" path (`D_00139F04`,
  `func_000E1030`) that looks files up elsewhere when set; it is not part of the
  header.
- Asset formats inside the archive.
