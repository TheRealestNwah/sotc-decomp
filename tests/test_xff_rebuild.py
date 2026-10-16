import struct

import pytest
from test_xff2 import make_module, sym

from tools.check import compare
from tools.xff2 import (
    SHT_DVP_OVERLAY_TABLE,
    SHT_PROGBITS,
    SHT_REL,
    RelTable,
    Section,
    parse,
    to_elf,
    write,
)
from tools.xff_rebuild import RebuildError, main, rebuild


def assembled_module():
    """GAS-like symbol/section ordering, zero import values and shuffled relocs."""
    module = make_module()
    order = [0, 4, 5, 6, 1, 2, 3, 7, 8, 9]
    sections = {old: new for new, old in enumerate(order)}
    module.sections = [module.sections[index] for index in order]
    old_symbols = [module.symbol(i) for i in range(module.num_symbols)]
    names = [module.symbol_name(i) for i in range(module.num_symbols)]
    module.strtab = b"\0imported\0entry\0local_fn\0"
    offsets = {name: module.strtab.index(name.encode() + b"\0") for name in names if name}
    permutation = [0, 2, 1, 4, 3]
    indices = {old: new for new, old in enumerate(permutation)}
    symbols = []
    for index in permutation:
        _, value, size, info, other, section = old_symbols[index]
        if section == 0:
            value = 0  # GAS does not emit the original undefined st_value.
        if index == 3:
            info, size = 0x10, 0  # Preserve original attributes in the XFF.
        symbols.append(
            struct.pack(
                "<IIIBBH",
                offsets.get(names[index], 0),
                value,
                size,
                info,
                other,
                sections[section] if section else 0,
            )
        )
    module.symbols = b"".join(symbols)
    module.sections[module.index_of(".symtab")].data = module.symbols
    for table in module.reltables:
        table.target = sections[table.target]
        table.entries = [
            (offset, (indices[info >> 8] << 8) | (info & 255), saved, extra)
            for offset, info, saved, extra in reversed(table.entries)
        ]
    module.imports = [indices[index] for index in module.imports]
    return module


def test_rebuild_restores_original_tables_from_reordered_assembled_object():
    original = write(make_module())
    assert rebuild(to_elf(assembled_module()), original) == original


@pytest.mark.parametrize("offset, value", [(16, 2), (18, 3)])
def test_non_mips_or_non_relocatable_object_is_rejected(offset, value):
    obj = bytearray(to_elf(assembled_module()))
    struct.pack_into("<H", obj, offset, value)
    with pytest.raises(RebuildError, match="ELF32 MIPS relocatable"):
        rebuild(bytes(obj), write(make_module()))


def test_unmodeled_template_header_fields_are_rejected():
    template = bytearray(write(make_module()))
    struct.pack_into("<I", template, 4, 1)
    with pytest.raises(RebuildError, match="metadata the XFF writer cannot reproduce"):
        rebuild(to_elf(assembled_module()), bytes(template))


def test_nonempty_unstored_payload_cannot_hide_assembled_bytes():
    module = make_module()
    module.sections[module.index_of(".data")].data = None
    with pytest.raises(RebuildError, match="nonempty payload is not stored"):
        rebuild(to_elf(assembled_module()), write(module))


def test_extra_allocated_payload_cannot_be_discarded():
    module = assembled_module()
    offset = len(module.shstrtab)
    module.shstrtab += b".data.extra\0"
    module.sections[module.index_of(".shstrtab")].size = len(module.shstrtab)
    module.sections.append(Section(offset, SHT_PROGBITS, 4, 4, bytes(4)))
    with pytest.raises(RebuildError, match="unexpected allocated section .data.extra"):
        rebuild(to_elf(module), write(make_module()))


def test_duplicate_section_names_are_rejected():
    module = assembled_module()
    text = module.sections[module.index_of(".text")]
    module.sections.append(Section(text.name_offset, SHT_PROGBITS, 0, 4, b""))
    with pytest.raises(RebuildError, match="duplicate ELF section .text"):
        rebuild(to_elf(module), write(make_module()))


def test_duplicate_assembled_symbol_names_are_rejected():
    module = assembled_module()
    module.symbols += module.symbols[4 * 16 : 5 * 16]
    module.sections[module.index_of(".symtab")].data = module.symbols
    module.sections[module.index_of(".symtab")].size = len(module.symbols)
    with pytest.raises(RebuildError, match="duplicate assembled symbol entry"):
        rebuild(to_elf(module), write(make_module()))


def test_changed_symbol_binding_is_rejected():
    module = assembled_module()
    symbols = bytearray(module.symbols)
    symbols[4 * 16 + 12] = 0  # entry loses its global binding
    module.symbols = bytes(symbols)
    module.sections[module.index_of(".symtab")].data = module.symbols
    with pytest.raises(RebuildError, match="symbol binding differs"):
        rebuild(to_elf(module), write(make_module()))


def test_nonempty_rela_section_is_rejected():
    module = assembled_module()
    module.sections[module.index_of(".rela.text")].size = 12
    with pytest.raises(RebuildError, match="nonempty RELA"):
        rebuild(to_elf(module), write(make_module()))


def test_changed_assembled_payload_and_saved_relocation_word_are_not_hidden():
    module = assembled_module()
    section = module.sections[module.index_of(".text")]
    data = bytearray(section.data)
    struct.pack_into("<I", data, 8, 0x0C000123)
    section.data = bytes(data)
    original = write(make_module())
    result = rebuild(to_elf(module), original)
    assert not compare(result, original)[0]
    rebuilt = parse(result)
    assert rebuilt.sections[rebuilt.index_of(".text")].data == bytes(data)
    assert rebuilt.reltables[0].entries[0][2] == 0x0C000123


@pytest.mark.parametrize("section", [".text", ".bss"])
def test_wrong_payload_size_is_rejected(section):
    module = assembled_module()
    module.sections[module.index_of(section)].size += 4
    if section == ".text":
        module.sections[module.index_of(section)].data += bytes(4)
    with pytest.raises(RebuildError, match="section type or size"):
        rebuild(to_elf(module), write(make_module()))


def test_original_defined_symbol_cannot_become_an_import():
    module = assembled_module()
    symbols = bytearray(module.symbols)
    struct.pack_into("<H", symbols, 4 * 16 + 14, 0)  # entry
    module.symbols = bytes(symbols)
    module.sections[module.index_of(".symtab")].data = module.symbols
    with pytest.raises(RebuildError, match="entry: expected"):
        rebuild(to_elf(module), write(make_module()))


def test_moved_defined_symbol_is_rejected():
    module = assembled_module()
    symbols = bytearray(module.symbols)
    struct.pack_into("<I", symbols, 4 * 16 + 4, 12)
    module.symbols = bytes(symbols)
    module.sections[module.index_of(".symtab")].data = module.symbols
    with pytest.raises(RebuildError, match="entry: expected"):
        rebuild(to_elf(module), write(make_module()))


@pytest.mark.parametrize("change", ["target", "type", "extra", "duplicate", "unaligned"])
def test_invalid_assembled_relocations_are_rejected(change):
    module = assembled_module()
    table = module.reltables[0]
    offset, info, saved, extra = table.entries[0]
    if change == "target":
        table.entries[0] = (offset, (4 << 8) | (info & 255), saved, extra)
    elif change == "type":
        table.entries[0] = (offset, (info & ~255) | 2, saved, extra)
    elif change == "extra":
        table.entries.append((28, info, 0, extra))
    elif change == "duplicate":
        table.entries.append(table.entries[0])
    else:
        table.entries[0] = (offset + 1, info, saved, extra)
    with pytest.raises(RebuildError, match="relocation"):
        rebuild(to_elf(module), write(make_module()))


def overlay_module():
    module = make_module()
    for name, kind, data, size in [
        (".DVP.ovlytab", SHT_DVP_OVERLAY_TABLE, struct.pack("<I", 0x10), 4),
        (".rel.DVP.ovlytab", SHT_REL, None, 8),
    ]:
        offset = len(module.shstrtab)
        module.shstrtab += name.encode() + b"\0"
        module.sections.append(Section(offset, kind, size, 4, data))
    module.sections[module.index_of(".shstrtab")].size = len(module.shstrtab)
    module.symbols += sym(0, 0, 0, 3, 10)  # Metadata-only section symbol.
    module.sections[module.index_of(".symtab")].data = module.symbols
    module.sections[module.index_of(".symtab")].size = len(module.symbols)
    module.reltables += [RelTable(10, True), RelTable(10, False, [(0, 0x102, 0x10, 0)])]
    module.reltables.sort(key=lambda table: not table.is_import)
    return module


def test_non_emitted_dvp_metadata_and_its_relocations_are_retained_explicitly():
    original = write(overlay_module())
    assert rebuild(to_elf(make_module()), original) == original


def test_conflicting_supplied_dvp_metadata_is_rejected():
    module = overlay_module()
    original = write(module)
    module.sections[10].data = bytes(4)
    with pytest.raises(RebuildError, match="metadata differs"):
        rebuild(to_elf(module), original)


def test_conflicting_supplied_dvp_relocation_is_rejected():
    module = overlay_module()
    original = write(module)
    module.reltables[-1].entries[0] = (0, 0x302, 0x10, 0)
    with pytest.raises(RebuildError, match="metadata relocations differ"):
        rebuild(to_elf(module), original)


def test_cli_rebuilds_and_rejects_invalid_object_without_writing(tmp_path, capsys):
    template = tmp_path / "original.XFF"
    template.write_bytes(write(make_module()))
    obj = tmp_path / "assembled.o"
    obj.write_bytes(to_elf(assembled_module()))
    output = tmp_path / "out/rebuilt.XFF"
    assert main([str(obj), str(template), str(output)]) == 0
    assert output.read_bytes() == template.read_bytes()
    bad_output = tmp_path / "bad.XFF"
    obj.write_bytes(b"not an ELF")
    assert main([str(obj), str(template), str(bad_output)]) == 1
    assert not bad_output.exists()
    assert "XFF rebuild:" in capsys.readouterr().err


def test_cli_reports_truncated_template_without_writing(tmp_path, capsys):
    template, obj, output = (tmp_path / name for name in ["original.XFF", "in.o", "out.XFF"])
    template.write_bytes(b"xff2")
    obj.write_bytes(to_elf(assembled_module()))
    assert main([str(obj), str(template), str(output)]) == 1
    assert not output.exists()
    assert "XFF rebuild:" in capsys.readouterr().err
