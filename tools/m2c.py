"""First C draft of an XFF function with m2c.

    python tools/m2c.py getMinAmbient
    python tools/m2c.py func_000C0D48 --through func_000C0E78 --module GAMECORE
    python tools/m2c.py getMinAmbient --context ctx.c   # other options go to m2c
    python tools/m2c.py getMinAmbient --ee-context native-ee-types.c

m2c (github.com/matt-kempster/m2c) decompiles MIPS assembly into C. The
output is a starting point: it has the right control flow and data accesses,
but it rarely matches as-is. It lives outside the repo, at $SOTC_M2C
(default D:/Modding/decomp-tools/m2c).

The function is taken from asm/xff/<MODULE>/text.s and cleaned up for m2c:
- local twin labels (.Lxff.name) become plain names;
- words the split had to emit raw (an explicit .reloc plus .word) are put
  back as the instruction spimdisasm wrote in the comment.
spimdisasm sometimes ends a function at a tail call and labels the rest
func_XXXXXXXX; --through LABEL includes everything up to that label's end.
"""

from __future__ import annotations

import argparse
import io
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
M2C = Path(os.environ.get("SOTC_M2C", "D:/Modding/decomp-tools/m2c"))
RAW_WORD_RE = re.compile(r"^(\s*/\*[^*]*\*/\s*)\.word\s+0x[0-9A-Fa-f]+\s*/\*\s*(.*?)\s*\*/\s*$")


def extract(lines: list[str], name: str, through: str | None) -> list[str]:
    try:
        first = next(
            i
            for i, line in enumerate(lines)
            if re.match(rf"\s*\w+label\s+{re.escape(name)}\b", line)
        )
    except StopIteration:
        raise SystemExit(f"{name}: no such label") from None
    last_label = through or name
    for i in range(first, len(lines)):
        if re.match(rf"\s*end\w*label\s+{re.escape(last_label)}\b", lines[i]):
            body = lines[first : i + 1]
            # One function for m2c: drop the split's inner function boundaries.
            inner = re.compile(r"\s*(glabel|dlabel|end\w*label|nonmatching)\b")
            body = [body[0]] + [x for x in body[1:-1] if not inner.match(x)] + [body[-1]]
            # m2c interprets a plain func_XXXXXXXX label as another function.
            # Split tails and their references must stay local to this draft.
            aliases = {
                x.strip()[:-1]
                for x in body
                if x.startswith(".Lxff.") and x.endswith(":") and x != f".Lxff.{name}:"
            }
            for alias in aliases:
                plain = alias.removeprefix(".Lxff.")
                local = alias.replace(".Lxff.", ".Lm2c.")
                # spimdisasm may emit both a plain label and its local twin.
                # Leaving the plain definition makes m2c start another function.
                body = [x for x in body if x.strip() != f"{plain}:"]
                body = [
                    re.sub(
                        rf"(?<![\w.]){re.escape(plain)}(?![\w.])",
                        local,
                        re.sub(re.escape(alias) + r"(?![\w.])", local, x),
                    )
                    for x in body
                ]
            return body
    raise SystemExit(f"{last_label}: no endlabel after {name}")


DATA_WORD_RE = re.compile(
    r"^\s*/\* [0-9A-F]+ ([0-9A-F]+) [0-9A-F]+ \*/\s*\.word\s+0x([0-9A-Fa-f]+)"
)
RELOC_RE = re.compile(r'^\s*\.reloc \., (R_MIPS_\w+), "?([^"\s]+)"?')
RELOC_FORMS = {"R_MIPS_HI16": "%hi({})", "R_MIPS_LO16": "%lo({})", "R_MIPS_26": "{}"}


SECTION_PREFIXES = {".text": "func", ".data": "D", ".rodata": "RO", ".bss": "B"}


def sext16(value: int) -> int:
    return (value & 0xFFFF) - 0x10000 if value & 0x8000 else value & 0xFFFF


def reloc_names(lines: list[str], section_bases: dict[str, int]) -> dict[int, str]:
    """Line index -> symbol for each relocated .word. Section-relative
    references get the asm label name of their target (D_0017B1B4 style),
    pairing %hi with the next %lo of the same section for the address."""
    sites = []  # (line index, type, target, word)
    pending = None
    for i, line in enumerate(lines):
        m = RELOC_RE.match(line)
        if m:
            pending = m.groups()
            continue
        m = DATA_WORD_RE.match(line)
        if m and pending:
            sites.append((i, pending[0], pending[1].replace(".Lxff.", ""), int(m.group(2), 16)))
        pending = None
    names = {}
    for k, (i, rtype, target, word) in enumerate(sites):
        section = target[len("start") :] if target.startswith("start.") else None
        if rtype == "R_MIPS_26":
            offset = (word & 0x3FFFFFF) << 2
        elif rtype == "R_MIPS_HI16":
            lo = next((s[3] for s in sites[k + 1 :] if s[1] == "R_MIPS_LO16" and s[2] == target), 0)
            offset = ((word & 0xFFFF) << 16) + sext16(lo)
        else:
            hi = next(
                (s[3] for s in reversed(sites[:k]) if s[1] == "R_MIPS_HI16" and s[2] == target), 0
            )
            offset = ((hi & 0xFFFF) << 16) + sext16(word)
        if section is None or section not in section_bases:
            suffix = f" {'+' if offset > 0 else '-'} 0x{abs(offset):X}" if offset else ""
            names[i] = target + suffix
            continue
        prefix = SECTION_PREFIXES.get(section, "D")
        names[i] = f"{prefix}_{section_bases[section] + offset:08X}"
    return names


def disassemble_words(lines: list[str], section_bases: dict[str, int] | None = None) -> list[str]:
    """Code that spimdisasm emitted as .word data (functions only reached
    through pointers) becomes instructions, with labels for branch targets.
    Mnemonic comments are reused unless an authoritative HI16/LO16 relocation
    can correct their address operand. Jump comments keep extracted local aliases."""
    import rabbitizer  # comes with spimdisasm

    names = reloc_names(lines, section_bases or {})
    out, targets, reloc = [], set(), None
    for i, line in enumerate(lines):
        m = RELOC_RE.match(line)
        if m:
            reloc = m.groups()
            out.append(line)
            continue
        m = DATA_WORD_RE.match(line)
        comment = RAW_WORD_RE.match(line)
        relocated = False
        if reloc and reloc[0] in {"R_MIPS_HI16", "R_MIPS_LO16"}:
            target = reloc[1].removeprefix(".Lxff.")
            relocated = not target.startswith("start.") or target[5:] in (section_bases or {})
        if not m or (
            comment and not comment.group(2).lstrip().startswith(".word") and not relocated
        ):
            out.append(line)
            reloc = None
            continue
        address, word = int(m.group(1), 16), int(m.group(2), 16)
        category = rabbitizer.InstrCategory.R5900
        # R5900 disassembly emits even valid cvt.w.s as .word, which m2c
        # ignores. Decode this canonical encoding with the CPU decoder.
        # Keep the reserved ft field zero and leave other formats untouched.
        if word & 0xFFFF003F == 0x46000024:
            category = rabbitizer.InstrCategory.CPU
        insn = rabbitizer.Instruction(word, address, category)
        override = None
        if reloc and reloc[0] in RELOC_FORMS:
            override = RELOC_FORMS[reloc[0]].format(names.get(i, reloc[1]))
        elif insn.isBranch():
            override = f".L{insn.getBranchVramGeneric():08X}"
            targets.add(insn.getBranchVramGeneric())
        reloc = None
        if not insn.isValid():
            out.append(line)
            continue
        out.append(f"    /* {address:06X} */ {insn.disassemble(immOverride=override)}")
    labelled = []
    for line in out:
        m = re.match(r"^\s*/\* ([0-9A-F]{6}) \*/", line) or re.match(
            r"^\s*/\* [0-9A-F]+ ([0-9A-F]+) ", line
        )
        if m and int(m.group(1), 16) in targets:
            labelled.append(f".L{int(m.group(1), 16):08X}:")
        labelled.append(line)
    return labelled


def clean(lines: list[str], section_bases: dict[str, int] | None = None) -> list[str]:
    out = []
    for line in disassemble_words(lines, section_bases):
        if line.strip().startswith(".reloc "):
            continue
        m = RAW_WORD_RE.match(line)
        if m:
            line = m.group(1) + m.group(2)
        out.append(line.replace(".Lxff.", ""))
    return out


def section_bases(module: str) -> dict[str, int]:
    """File offset of each section of the original module (the asm's addresses)."""
    from elftools.elf.elffile import ELFFile

    from tools.xff2 import parse, to_elf

    elf = ELFFile(io.BytesIO(to_elf(parse((ROOT / f"iso/{module}.XFF").read_bytes()))))
    return {s.name: s["sh_offset"] for s in elf.iter_sections() if s.name}


def ee_context(source: str) -> str:
    """Represent native EE 8-byte integer long as m2c's 8-byte long long.

    Context must be self-contained C declarations, without preprocessor directives.
    Preserve comments/literals and the other native 8-byte spellings (long long
    and long double). Never rewrite the user's file or the external decompiler.
    """
    tokens = re.findall(
        r'/\*[\s\S]*?\*/|//[^\r\n]*|"(?:\\.|[^"\\])*"|'
        r"'(?:\\.|[^'\\])*'|[A-Za-z_]\w*|\s+|.",
        source,
    )
    significant = [
        i
        for i, token in enumerate(tokens)
        if not token.isspace() and not token.startswith(("/*", "//"))
    ]
    if any(tokens[i] == "#" for i in significant):
        raise ValueError(
            "--ee-context requires self-contained declarations without preprocessor directives"
        )
    specifiers = {
        "long",
        "short",
        "signed",
        "unsigned",
        "int",
        "char",
        "float",
        "double",
        "void",
        "const",
        "volatile",
        "restrict",
        "typedef",
        "extern",
        "static",
        "register",
        "auto",
    }
    replacements = []
    for position, index in enumerate(significant):
        if tokens[index] != "long":
            continue
        start = end = position
        while start and tokens[significant[start - 1]] in specifiers:
            start -= 1
        while end + 1 < len(significant) and tokens[significant[end + 1]] in specifiers:
            end += 1
        group = [tokens[i] for i in significant[start : end + 1]]
        if group.count("long") == 1 and "double" not in group:
            replacements.append(index)
    for index in replacements:
        tokens[index] += " long"
    return "".join(tokens)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("function")
    parser.add_argument("--module", default="GAMECORE")
    parser.add_argument("--through", help="include spimdisasm's split-off rest up to this label")
    parser.add_argument(
        "--ee-context",
        action="append",
        type=Path,
        default=[],
        metavar="FILE",
        help="native EE declarations: adapt 8-byte long for m2c; no preprocessor directives",
    )
    args, m2c_args = parser.parse_known_args(argv)  # the rest goes to m2c

    text = ROOT / f"asm/xff/{args.module.upper()}/text.s"
    lines = text.read_text(encoding="latin-1").splitlines()
    body = clean(extract(lines, args.function, args.through), section_bases(args.module.upper()))
    # m2c only treats glabel as a function start; alabel/jlabel are fine as labels.
    body[0] = re.sub(r"^\s*\w+label", "glabel", body[0])
    with tempfile.TemporaryDirectory() as tmp:
        asm = Path(tmp) / "fn.s"
        asm.write_text("\n".join(body) + "\n", encoding="latin-1")
        for index, context in enumerate(args.ee_context):
            try:
                source = ee_context(context.read_text(encoding="utf-8"))
            except ValueError as error:
                parser.error(str(error))
            converted = Path(tmp) / f"ee-context-{index}.c"
            converted.write_text(source, encoding="utf-8")
            m2c_args.extend(["--context", str(converted)])
        result = subprocess.run(
            [sys.executable, str(M2C / "m2c.py"), "-t", "mipsee-gcc-c", *m2c_args, str(asm)]
        )
    return result.returncode


if __name__ == "__main__":
    sys.exit(main())
