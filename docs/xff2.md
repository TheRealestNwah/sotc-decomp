# The `xff2` module format

`KERNEL.XFF`, `MANAGER.XFF` and `GAMECORE.XFF` hold nearly all of the game's code. Each is an **ELF relocatable object (`ET_REL`) in a custom wrapper**:
- The section contents, `Elf32_Sym` symbol table, string tables and `Elf32_Rel` relocations are stored as-is.
- The ELF header and section headers are replaced by a custom header and section table.
- The relocations are split into import and local tables, with a copy of each relocated word.

`tools/xff2.py` reads and writes the format and converts to and from a standard ELF object. XFF → ELF → XFF reproduces all three modules byte for byte.

All values are little-endian `u32` unless noted. "Pointer" fields hold the file offset plus `0x40010000`, and every pointer is repeated as a plain file offset in words 20–27.

## Header (`0x70` bytes)

| Word | Meaning |
| ---: | --- |
| 0 | Magic `xff2` |
| 1, 2, 4, 6 | Always 0 |
| 3 | Number of local symbols, not counting the null symbol (ELF `.symtab` `sh_info` − 1) |
| 5 | File size |
| 7 | Number of imports (undefined symbols) |
| 8 | Pointer: imports array |
| 9 | Number of symbols |
| 10 | Pointer: symbol table |
| 11 | Pointer: symbol string table |
| 12 | Pointer: section table |
| 13 | Pointer: symbol address array |
| 14 | Number of relocation tables |
| 15 | Pointer: relocation table descriptors |
| 16 | Number of sections |
| 17 | Pointer: section name offsets |
| 18 | Pointer: section name string table (`.shstrtab`) |
| 19 | Entry point: offset into `.text` (lands on `ioskernel`, `entrymanager` and `gamecore`) |
| 20–27 | File offsets for words 8, 10, 11, 12, 13, 15, 17, 18 |

## Tables

- **Section name offsets:** one `u32` per section, an offset into `.shstrtab`. This is the ELF `sh_name`.
- **Section table:** `0x20` bytes per section:

  | Word | Meaning |
  | ---: | --- |
  | 0 | 0 |
  | 1 | Pointer to the contents, or 0 if not stored |
  | 2 | Size |
  | 3 | Alignment |
  | 4 | ELF section type |
  | 5 | 1 for `SHT_NOBITS` (`.bss`, `.vubss`), else 0 |
  | 6 | 0 |
  | 7 | File offset of the contents, or 0 |

  ELF flags, `sh_link` and `sh_info` aren't stored. They follow from the section names and the relocation tables.
- **Symbol address array:** one `u32` per symbol, always equal to that symbol's `st_value`.
- **Relocation table descriptors:** `0x1c` bytes each: `SHT_REL`, entry count, target section index, pointer A, pointer B, offset A, offset B.
  - There are two tables for every section that has a `.rel` section. The first half of the list holds **imports** (relocations against undefined symbols), the second half **locals**.
  - **Array A** is the standard `Elf32_Rel` (`r_offset`, `r_info`).
  - **Array B** is parallel to it, 8 bytes per entry. The first word is the unrelocated word at the relocation site, which also appears in the section data. The second word is 0 for locals. For imports it is a relocation-info-like value that isn't fully understood yet: often equal to `r_info`, but not always. `tools/xff2.py` keeps these in an extra ELF section, `.xff.relinfo`.
- **Imports array:** the symbol index of each undefined symbol, in order.

## File layout

In order, with zero padding:
1. Header.
2. Section name offsets, section table, symbol address array, relocation descriptors, imports array.
3. `.shstrtab`.
4. Section contents for every `SHT_PROGBITS`, `SHT_SYMTAB` and `.DVP.ovlytab` section, in section-index order, each aligned to `max(sh_addralign, 4)`. `.strtab` follows `.symtab` directly.
5. The relocation arrays, aligned to 4: all import B arrays, all import A arrays, all local A arrays, then all local B arrays.

Descriptors for empty tables point at the current A/B positions.

## Notes

- **Section data is unrelocated.** Every relocation site still holds its original word, so the contents are exactly what the assembler or linker produced.
- **Unstored contents:** `.reginfo`, `.DVP.ovlystrtab` and the `.DVP.overlay..*` sections (MANAGER's VU microcode overlay metadata) have sizes but no stored contents. The ELF conversion zero-fills them.
- **Undefined symbols' values:** some have nonzero `st_value`. They're kept as-is.
- **Symbols:** KERNEL has 1,915 symbols and no imports. MANAGER has 2,818 symbols and 433 imports, and also carries `.vutext` (VU microcode) plus the DVP overlay tables. GAMECORE has 4,646 symbols and 1,849 imports.
