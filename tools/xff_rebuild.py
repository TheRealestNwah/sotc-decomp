"""Rebuild an XFF from assembled ELF sections and an original metadata template.

    python tools/xff_rebuild.py build/xff/KERNEL/KERNEL.o iso/KERNEL.XFF build/xff/KERNEL.XFF

Code/data, symbol locations and relocations are supplied or verified by the ELF.
The template supplies original table order and metadata absent from assembly;
see docs/xff2.md. Compare the resulting file with the original separately.
"""

from __future__ import annotations

import argparse
import io
import struct
import sys
from pathlib import Path

from elftools.common.exceptions import ELFError
from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from tools.xff2 import SHT_NOBITS, SHT_PROGBITS, SHT_SYMTAB, parse, to_elf, write  # noqa: E402


class RebuildError(ValueError):
    pass


def symbol_key(elf: ELFFile, symbol) -> tuple[str, str]:
    if symbol["st_info"]["type"] == "STT_SECTION":
        return "section", elf.get_section(symbol["st_shndx"]).name
    return "symbol", symbol.name


def location(elf: ELFFile, symbol) -> tuple[str, int]:
    index = symbol["st_shndx"]
    return (
        elf.get_section(index).name if isinstance(index, int) else index,
        symbol["st_value"],
    )


def relocations(
    elf: ELFFile, section: str, indices: dict[tuple[str, str], int], size: int
) -> dict[int, int]:
    rel = elf.get_section_by_name(".rel" + section)
    result = {}
    if rel is None:
        return result
    if rel["sh_type"] != "SHT_REL" or elf.get_section(rel["sh_info"]).name != section:
        raise RebuildError(f"{section}: invalid relocation section")
    symtab = elf.get_section(rel["sh_link"])
    for entry in rel.iter_relocations():
        offset = entry["r_offset"]
        if not 0 <= offset <= size - 4 or offset % 4:
            raise RebuildError(f"{section}: relocation outside section or unaligned at {offset:#x}")
        if offset in result:
            raise RebuildError(f"{section}: duplicate relocation at {offset:#x}")
        key = symbol_key(elf, symtab.get_symbol(entry["r_info_sym"]))
        if key not in indices:
            raise RebuildError(f"{section}: relocation refers to unknown symbol {key}")
        result[offset] = (indices[key] << 8) | entry["r_info_type"]
    return result


def rebuild(assembled: bytes, template: bytes) -> bytes:
    module = parse(template)
    if write(module) != template:
        raise RebuildError("template contains metadata the XFF writer cannot reproduce")
    original = ELFFile(io.BytesIO(to_elf(module)))
    elf = ELFFile(io.BytesIO(assembled))
    if (
        elf.elfclass != 32
        or not elf.little_endian
        or elf["e_type"] != "ET_REL"
        or elf["e_machine"] != "EM_MIPS"
    ):
        raise RebuildError("expected a little-endian ELF32 MIPS relocatable object")

    sections = {}
    for section in elf.iter_sections():
        if section.name in sections:
            raise RebuildError(f"duplicate ELF section {section.name}")
        sections[section.name] = section
        if section["sh_type"] == "SHT_RELA" and section["sh_size"]:
            raise RebuildError(f"{section.name}: nonempty RELA sections are unsupported")
        if (
            section["sh_type"] in ("SHT_PROGBITS", "SHT_NOBITS")
            and section["sh_flags"] & 2
            and section["sh_size"]
            and original.get_section_by_name(section.name) is None
        ):
            raise RebuildError(f"unexpected allocated section {section.name}")

    payloads = set()
    for index, target in enumerate(module.sections):
        name = module.section_name(index)
        supplied = sections.get(name)
        if target.type not in (SHT_PROGBITS, SHT_NOBITS):
            # DVP overlay tables/headers and other non-payload metadata come
            # from the template. Reject a conflicting supplied metadata blob.
            if target.data is not None and target.type != SHT_SYMTAB and supplied is not None:
                if supplied.data() != target.data:
                    raise RebuildError(f"{name}: supplied metadata differs from template")
            continue
        payloads.add(name)
        if target.type == SHT_PROGBITS and target.size and target.data is None:
            raise RebuildError(f"{name}: nonempty payload is not stored in template")
        kind = "SHT_NOBITS" if target.type == SHT_NOBITS else "SHT_PROGBITS"
        if supplied is None:
            if target.size:
                raise RebuildError(f"{name}: missing payload section")
            continue
        if supplied["sh_type"] != kind or supplied["sh_size"] != target.size:
            raise RebuildError(f"{name}: section type or size differs from original layout")
        if target.type == SHT_PROGBITS and target.data is not None:
            target.data = supplied.data()

    orig_symbols = list(original.get_section_by_name(".symtab").iter_symbols())
    indices = {}
    for index, symbol in enumerate(orig_symbols):
        key = symbol_key(original, symbol)
        if key in indices:
            raise RebuildError(f"ambiguous original symbol {key}")
        indices[key] = index
    symtab = elf.get_section_by_name(".symtab")
    if symtab is None:
        raise RebuildError("assembled object has no symbol table")
    supplied_symbols = {}
    for symbol in symtab.iter_symbols():
        if symbol.name and symbol["st_info"]["type"] != "STT_SECTION":
            if symbol.name in supplied_symbols:
                raise RebuildError(f"duplicate assembled symbol {symbol.name}")
            supplied_symbols[symbol.name] = symbol
    symbols = bytearray(module.symbols)
    for index, symbol in enumerate(orig_symbols):
        if index == 0 or symbol["st_info"]["type"] == "STT_SECTION":
            continue
        supplied = supplied_symbols.get(symbol.name)
        if supplied is None:
            raise RebuildError(f"missing assembled symbol {symbol.name}")
        if supplied["st_info"]["bind"] != symbol["st_info"]["bind"]:
            raise RebuildError(f"{symbol.name}: symbol binding differs")
        expected = location(original, symbol)
        actual = location(elf, supplied)
        if expected[0] == "SHN_UNDEF":
            if actual[0] != "SHN_UNDEF":
                raise RebuildError(f"{symbol.name}: original import became defined")
            # Undefined st_value fields carry metadata not emitted by GAS.
        else:
            if expected != actual:
                raise RebuildError(f"{symbol.name}: expected {expected}, assembled {actual}")
            struct.pack_into("<I", symbols, index * 16 + 4, supplied["st_value"])
    module.symbols = bytes(symbols)
    module.sections[module.index_of(".symtab")].data = module.symbols

    for section in elf.iter_sections():
        if section["sh_type"] == "SHT_REL" and section["sh_size"]:
            name = elf.get_section(section["sh_info"]).name
            if name not in payloads and (
                not name.startswith(".DVP.") or original.get_section_by_name(name) is None
            ):
                raise RebuildError(f"unexpected relocation target section {name}")
    for name in payloads:
        index = module.index_of(name)
        tables = [table for table in module.reltables if table.target == index]
        expected = {}
        for table in tables:
            for offset, info, _, _ in table.entries:
                if offset in expected:
                    raise RebuildError(f"{name}: duplicate original relocation at {offset:#x}")
                expected[offset] = info
        actual = relocations(elf, name, indices, module.sections[index].size)
        if actual != expected:
            raise RebuildError(f"{name}: assembled relocation sites, types or targets differ")
        for table in tables:
            data = module.sections[index].data or b""
            table.entries = [
                (offset, actual[offset], struct.unpack_from("<I", data, offset)[0], extra)
                for offset, _, _, extra in table.entries
            ]
    # Metadata relocation tables (notably .DVP.ovlytab) retain their original
    # order and opaque fields. Their contents are not emitted by the splitter.
    for index, target in enumerate(module.sections):
        name = module.section_name(index)
        if name.startswith(".DVP.") and elf.get_section_by_name(".rel" + name) is not None:
            expected = {
                offset: info
                for table in module.reltables
                if table.target == index
                for offset, info, _, _ in table.entries
            }
            if relocations(elf, name, indices, target.size) != expected:
                raise RebuildError(f"{name}: supplied metadata relocations differ")
    return write(module)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("assembled", type=Path)
    parser.add_argument("template", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args(argv)
    try:
        data = rebuild(args.assembled.read_bytes(), args.template.read_bytes())
    except (ELFError, ValueError, struct.error) as error:
        print(f"XFF rebuild: {error}", file=sys.stderr)
        return 1
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(data)
    print(f"{args.output}: rebuilt {len(data)} bytes using original layout metadata")
    return 0


if __name__ == "__main__":
    sys.exit(main())
