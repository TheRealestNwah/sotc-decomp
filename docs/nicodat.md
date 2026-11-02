# NICO.DAT

`NICO.DAT` is the archive on the disc that holds almost all of the game's assets
([ADR 0008](adr/0008-assets-from-the-owners-disc-image.md)). This page describes its
header as the Original reads it. The Native port's parser is
[`port/disc/nicodat.c`](../port/disc/nicodat.c).

The layout comes from the Game modules' code and has been checked against the
owner's US Disc image with `nicoinfo` (`nicoinfo <image> --all` prints every
table). The [US disc](#the-us-disc) section lists what that check found.

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
returns the second word of a direct-file record as a size in bytes.
`sheetFsLoadAdpcmInt` adds a sector offset to the first word of an ADPCM record
and reads from there with `sceCdReadIOPm` (through `iosIopRead`), without using
the second word. On the US disc every size, ADPCM included, is a byte count that
fits before the next record's sector.

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
| tex segs | `t` × (`s32` x, `s32` y, `u32` seg) |

`sheetFsLoadMap(name, dataType, variant, index, ...)` takes the table for
`dataType` (0 to 2) and `variant` (0 or 1) and starts the stream at that table's
record `index`. The tex seg entries go to a separate 12-byte-per-map table.
They are the cells of a 10 × 10 grid of world coordinates: x and y, then the
cell's texture segment. `sheetFsGetStageTexSegIndex(x, y)` returns the `seg` of
the first map's entry `(4 - y) * 10 + (x + 5) % 10`, which is the cell at
(x, y) because the entries are stored row by row, y from 4 down to -5 and x from
-5 to 4. The game itself never reads the x and y words.

### Special file

The names block comes first, then one entry per name:

| Field | Type |
|---|---|
| names size | `u32` |
| names | `S` NUL-terminated strings |
| then for each special file: | |
| entry count `e` | `u32` |
| data size | `u32`, `e` × 16 on the US disc |
| data | `e` × special fs entry |

A special file is a *special fs*: a lookup table that redirects loads to copies
of files. `sheetFsSrhSpecialFs(name)` finds one by name and
`sheetFsSetSpecialFs` makes it current (`D_00139F04`). While one is current,
`sheetFsLoadSegmentIndex`, `sheetFsLoadStageTex` and `sheetFsLoadMap` first
build an 8-byte key and search it with `func_000E1030`; a hit gives the sector to
read from instead of the header tables.

### Special fs entry

| Bytes | Field |
|---|---|
| 0–7 | key |
| 8–11 | sector |
| 12–15 | size in bytes |

The key's first byte is its kind. `func_000E1030` compares it first, then
branches on it through the jump table at `RO_0011B800`:

| Kind | Key | Match | Built by |
|---|---|---|---|
| 0 | `s16` index at byte 4 | index | segment loads of type `"stage"` |
| 1 | `s16` index at byte 4 | index | segment loads of any other type |
| 2 | data type at byte 1, variant at 2, a fifth `sheetFsLoadMap` argument at 3, `u16` record index at 6 | all 8 bytes (bytes 4 and 5 zeroed) | `sheetFsLoadMap` |
| 3, 4 | `s16` index at byte 4 | index | none found |

Kinds 0 to 2 return the entry's sector. Kinds 3 and 4 return the word at
`entry + 8 + sheetFsLanguageCode * 8`, the sector of a per-language slot. The map
name is not part of a map key, so a special fs only redirects loads of one map.

On the US disc, kind 3 entries point at segment index entries with bit 15 set
(localized ones), and their size is that of the localized record. No caller in
MANAGER builds a kind 3 or 4 key, and with language code 1 the read would land
on the next entry's key, so how (or whether) these entries are reached is still
open.

## The US disc

Checked against the owner's `Shadow of the Colossus (USA)` image (`SCUS-97472`,
image SHA1 `bd5dcb38bc1a08b261accd1b53894ee4e934788f`). `NICO.DAT` is at LSN
2604 and is 2,667,340,678 bytes; its header is 139,746 bytes, and the parser
reads it with no errors or leftover counts.

- Two segment types: `stage` (1,889 index entries, 1,773 files, 116 localized)
  and `stagetexseg_def` (112 index entries and files, none localized). Each
  localized entry has its own start (0 to 115), so this disc has one language
  and `sheetFsLanguageCode` 1 selects it.
- One map, `test`, with 3,600 records for data types 0 and 1 (both variants),
  none for data type 2, and 100 tex segs.
- 288 ADPCM records (all sizes are whole sectors) and 11 direct files.
- Six special fs: `common` (3 entries), `boot` (1), `startChara` (5),
  `op1_stage` (15), `op1` (4) and `newgame` (18). Each entry's size equals the
  size of the file its key names. Their sectors (1,278,361 onward) start right
  after the last byte any header table points at, so each special fs keeps
  copies of its files together, presumably for faster streaming.

## Not covered

- Asset formats inside the archive.
