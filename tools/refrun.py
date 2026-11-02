"""Record and compare Reference runs (ADR 0016).

A Reference run is a folder under refruns/ (gitignored, it comes from the
disc) holding:

  run.json      manifest: Disc image, PCSX2 build, settings, start condition
  inputs.p2m2   PCSX2 Input Recording of the pads, from power-on
  state.jsonl   one line per frame: {"frame": <vsync count>, "fields": {...}}
  state.toml    copy of the state map the run was recorded with

The recorder polls game state from the Matching build running in PCSX2 over
PINE. Game modules are relocatable, so it first finds where the Loader put
each module's sections in EE RAM (see `locate`). See docs/reference-runs.md.

  python -m tools.refrun check-disc <disc image>
  python -m tools.refrun inputs refruns/<run>/inputs.p2m2
  python -m tools.refrun locate
  python -m tools.refrun record refruns/<run> --disc <disc image>
  python -m tools.refrun info refruns/<run>
  python -m tools.refrun diff refruns/<a> refruns/<b>
"""

from __future__ import annotations

import argparse
import hashlib
import json
import shutil
import struct
import sys
import time
import tomllib
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

from tools import disc, p2m2, xff2

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_MAP = REPO_ROOT / "config" / "refrun" / "state.toml"
BASEROM = REPO_ROOT / "config" / "baserom.json"
MODULE_DIR = REPO_ROOT / "iso"
MODULES = ("KERNEL", "MANAGER", "GAMECORE")
SCHEMA = 1

EE_RAM = (0x00100000, 0x02000000)  # the Loader and everything it loads live here
SHN_ABS = 0xFFF1
R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16 = 2, 5, 6
SIGNATURE_WORDS = 32

TYPES = {
    "u8": (1, "<B"), "u16": (2, "<H"), "u32": (4, "<I"), "u64": (8, "<Q"),
    "s8": (1, "<b"), "s16": (2, "<h"), "s32": (4, "<i"), "s64": (8, "<q"),
    "f32": (4, "<f"),
}  # fmt: skip


# --- Finding modules in EE RAM -------------------------------------------------


def _relocated_offsets(module: xff2.Module, section: int) -> set[int]:
    return {e[0] for t in module.reltables if t.target == section for e in t.entries}


def signatures(module: xff2.Module, section: int, count: int = 4):
    """Yield (offset, bytes) windows of the section that no relocation touches."""
    data = module.sections[section].data
    relocated = _relocated_offsets(module, section)
    size = SIGNATURE_WORDS * 4
    found, offset = 0, 0
    while offset + size <= len(data) and found < count:
        window = data[offset : offset + size]
        clean = not any(offset <= r < offset + size for r in relocated)
        if clean and len(set(struct.unpack(f"<{SIGNATURE_WORDS}I", window))) > SIGNATURE_WORDS // 2:
            yield offset, window
            found += 1
            offset += len(data) // (count + 1) or size
        else:
            offset += 4


def find_by_signature(module: xff2.Module, section: int, ram: bytes, ram_base: int) -> int | None:
    """Base address of a PROGBITS section, if a signature appears exactly once in RAM."""
    for offset, window in signatures(module, section):
        hit = ram.find(window)
        if hit < 0 or ram.find(window, hit + 1) >= 0:
            continue
        return ram_base + hit - offset
    return None


def _sext16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def bases_from_relocations(
    module: xff2.Module, located: dict[int, int], ram: bytes, ram_base: int
) -> dict[int, int]:
    """Infer section bases from relocated words inside already-located sections.

    A local relocation site holds `saved + base(target) + symbol value` once
    loaded, so `base = ram word - saved - value`. HI16/LO16 pairs carry the
    32-bit sum split across two instructions. Each section gets the most common
    answer.
    """
    votes: dict[int, Counter] = {}

    def word(section: int, offset: int) -> int | None:
        pos = located[section] + offset - ram_base
        return struct.unpack_from("<I", ram, pos)[0] if 0 <= pos <= len(ram) - 4 else None

    for table in module.reltables:
        if table.is_import or table.target not in located:
            continue
        # A run of HI16s pairs with the LO16s after it (one lui can feed several).
        pending: list[tuple[int, int, int]] = []
        previous = None
        for offset, info, saved, _ in table.entries:
            kind, sym = info & 0xFF, info >> 8
            _, value, _, _, _, shndx = module.symbol(sym)
            if kind == R_MIPS_HI16:
                if previous != R_MIPS_HI16:
                    pending = []
                pending.append((offset, saved, sym))
            elif kind == R_MIPS_LO16:
                lo = word(table.target, offset)
                for hi_off, hi_saved, hi_sym in pending:
                    hi = word(table.target, hi_off)
                    if hi_sym != sym or hi is None or lo is None:
                        continue
                    before = ((hi_saved & 0xFFFF) << 16) + _sext16(saved & 0xFFFF)
                    after = ((hi & 0xFFFF) << 16) + _sext16(lo & 0xFFFF)
                    base = (after - before - value) & 0xFFFFFFFF
                    votes.setdefault(shndx, Counter())[base] += 1
            elif kind == R_MIPS_32:
                now = word(table.target, offset)
                if now is not None:
                    base = (now - saved - value) & 0xFFFFFFFF
                    votes.setdefault(shndx, Counter())[base] += 1
            previous = kind
    allocated = {
        i
        for i, sec in enumerate(module.sections)
        if sec.type in (xff2.SHT_PROGBITS, xff2.SHT_NOBITS)
    }
    return {
        s: c.most_common(1)[0][0] for s, c in votes.items() if s in allocated and s not in located
    }


def locate(module: xff2.Module, ram: bytes, ram_base: int) -> dict[str, int]:
    """Map section name -> load address for every allocated section found."""
    text = module.index_of(".text")
    located: dict[int, int] = {}
    base = find_by_signature(module, text, ram, ram_base)
    if base is None:
        return {}
    located[text] = base
    while True:  # each newly found section may point at more
        new = bases_from_relocations(module, located, ram, ram_base)
        if not new:
            break
        located.update(new)
    for i, sec in enumerate(module.sections):
        if i not in located and sec.type == xff2.SHT_PROGBITS and sec.size:
            found = find_by_signature(module, i, ram, ram_base)
            if found is not None:
                located[i] = found
    return {module.section_name(i): b for i, b in sorted(located.items())}


def load_modules(directory: Path = MODULE_DIR) -> dict[str, xff2.Module]:
    return {name: xff2.parse((directory / f"{name}.XFF").read_bytes()) for name in MODULES}


# --- State map ----------------------------------------------------------------


@dataclass
class Field:
    name: str
    type: str
    count: int
    size: int  # bytes fields only
    module: str | None = None
    symbol: str | None = None
    section: str | None = None
    offset: int = 0
    address: int | None = None

    @property
    def width(self) -> int:
        return self.size if self.type == "bytes" else TYPES[self.type][0]


def _field(entry: dict) -> Field:
    kind = entry.get("type", "u32")
    if kind != "bytes" and kind not in TYPES:
        raise ValueError(f"{entry.get('name')}: unknown type {kind}")
    f = Field(
        name=entry["name"],
        type=kind,
        count=entry.get("count", 1),
        size=entry.get("size", 0),
        module=entry.get("module"),
        symbol=entry.get("symbol"),
        section=entry.get("section"),
        offset=entry.get("offset", 0),
        address=entry.get("address"),
    )
    if f.address is None and not (f.module and (f.symbol or f.section)):
        raise ValueError(f"{f.name}: give address, or module plus symbol or section")
    if kind == "bytes" and not f.size:
        raise ValueError(f"{f.name}: bytes fields need a size")
    return f


def load_map(path: Path) -> tuple[Field, list[Field]]:
    data = tomllib.loads(path.read_text(encoding="utf-8"))
    if data.get("schema") != SCHEMA:
        raise ValueError(f"{path}: expected schema = {SCHEMA}")
    frame = _field(data["frame"])
    if frame.type not in ("u32", "u64") or frame.count != 1:
        raise ValueError("the frame key must be a single u32 or u64")
    fields = [_field(e) for e in data.get("field", [])]
    names = [f.name for f in fields]
    if len(set(names)) != len(names):
        raise ValueError("field names must be unique")
    return frame, fields


def find_symbol(module: xff2.Module, name: str) -> tuple[int, int]:
    """(value, section index) of a named symbol, preferring a global over locals."""
    matches = [module.symbol(i) for i in range(module.num_symbols) if module.symbol_name(i) == name]
    if not matches:
        raise LookupError(f"no symbol {name}")
    best = max(matches, key=lambda s: s[3] >> 4 != 0)
    return best[1], best[5]


def address_of(f: Field, modules: dict[str, xff2.Module], bases: dict[str, dict[str, int]]) -> int:
    if f.address is not None:
        return f.address + f.offset
    module = modules[f.module]
    if f.symbol:
        value, shndx = find_symbol(module, f.symbol)
        if shndx == SHN_ABS:
            return value + f.offset
        section = module.section_name(shndx)
    else:
        section, value = f.section, 0
    try:
        return bases[f.module][section] + value + f.offset
    except KeyError:
        raise LookupError(f"{f.name}: {f.module} {section} not found in EE RAM") from None


def plan_reads(f: Field, address: int) -> list[tuple[int, int]]:
    if f.type == "bytes":
        start, end = address & ~7, (address + f.size * f.count + 7) & ~7
        return [(a, 8) for a in range(start, end, 8)]
    return [(address + i * f.width, f.width) for i in range(f.count)]


def decode(f: Field, address: int, values: list[int]):
    if f.type == "bytes":
        blob = b"".join(v.to_bytes(8, "little") for v in values)
        start = address - (address & ~7)
        items = [blob[start + i * f.size : start + (i + 1) * f.size].hex() for i in range(f.count)]
    else:
        width, fmt = TYPES[f.type]
        items = [struct.unpack(fmt, v.to_bytes(width, "little"))[0] for v in values]
    return items[0] if f.count == 1 else items


# --- Recording ----------------------------------------------------------------


def sha1_file(path: Path) -> str:
    digest = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def sha1_tree(path: Path) -> str:
    """Hash a file, or every file in a folder memory card, by relative path."""
    if path.is_file():
        return sha1_file(path)
    digest = hashlib.sha1()
    for p in sorted(q for q in path.rglob("*") if q.is_file()):
        digest.update(p.relative_to(path).as_posix().encode() + b"\0")
        digest.update(sha1_file(p).encode())
    return digest.hexdigest()


def check_disc(image: Path, module_dir: Path = MODULE_DIR) -> list[str]:
    """Problems found comparing a Disc image with the build this repo matches."""
    problems = []
    config = json.loads(BASEROM.read_text(encoding="utf-8"))
    loader = disc.read_file(image, config["elf_name"])
    if hashlib.sha1(loader).hexdigest() != config["sha1"]:
        problems.append(f"{config['elf_name']} does not match config/baserom.json")
    for name in MODULES:
        ours = module_dir / f"{name}.XFF"
        theirs = disc.read_file(image, f"{name}.XFF")
        if ours.is_file() and ours.read_bytes() != theirs:
            problems.append(f"{name}.XFF differs from iso/{name}.XFF")
    return problems


def locate_all(pine, modules: dict[str, xff2.Module]) -> dict[str, dict[str, int]]:
    ram = pine.read_block(EE_RAM[0], EE_RAM[1] - EE_RAM[0])
    return {name: locate(m, ram, EE_RAM[0]) for name, m in modules.items()}


class Snapshotter:
    """Reads the frame key, every field, and the key again in batched PINE calls."""

    def __init__(self, pine, frame: Field, fields: list[Field], modules, bases):
        self.pine = pine
        self.frame_read = plan_reads(frame, address_of(frame, modules, bases))[0]
        self.fields = [(f, address_of(f, modules, bases)) for f in fields]
        self.reads = [self.frame_read]
        for f, address in self.fields:
            self.reads += plan_reads(f, address)
        self.reads.append(self.frame_read)

    def frame(self) -> int:
        return self.pine.read([self.frame_read])[0]

    def snapshot(self, tries: int = 8) -> tuple[int, dict] | None:
        """(frame, fields) read within one frame, or None if every try straddled one."""
        for _ in range(tries):
            values = self.pine.read(self.reads)
            if values[0] != values[-1]:
                continue
            out, pos = {}, 1
            for f, address in self.fields:
                n = len(plan_reads(f, address))
                out[f.name] = decode(f, address, values[pos : pos + n])
                pos += n
            return values[0], out
        return None


def record(
    pine, run_dir: Path, map_path: Path, modules, *, max_frames=None, idle_timeout=30.0, log=print
):
    """Poll state each frame until stopped; returns summary stats for run.json."""
    frame, fields = load_map(map_path)
    log("Finding game modules in EE RAM...")
    while True:
        bases = locate_all(pine, modules)
        missing = [n for n in modules if ".text" not in bases[n]]
        if not missing:
            break
        log(f"  waiting for {', '.join(missing)} to load")
        time.sleep(1.0)
    for name, secs in bases.items():
        log(f"  {name}: " + ", ".join(f"{s}@{a:#x}" for s, a in secs.items()))
    snap = Snapshotter(pine, frame, fields, modules, bases)
    stats = {"frames": 0, "first_frame": None, "last_frame": None, "skipped": 0, "torn": 0}
    last, idle_since = None, time.monotonic()
    with (run_dir / "state.jsonl").open("w", encoding="utf-8") as out:
        try:
            while max_frames is None or stats["frames"] < max_frames:
                now = snap.frame()
                if now == last:
                    if time.monotonic() - idle_since > idle_timeout:
                        log("Frame counter stopped; ending the run.")
                        break
                    continue
                result = snap.snapshot()
                if result is None:
                    stats["torn"] += 1
                    continue
                key, values = result
                if last is not None and key > last + 1:
                    stats["skipped"] += key - last - 1
                out.write(json.dumps({"frame": key, "fields": values}) + "\n")
                stats["frames"] += 1
                stats["first_frame"] = key if stats["first_frame"] is None else stats["first_frame"]
                stats["last_frame"] = last = key
                idle_since = time.monotonic()
        except KeyboardInterrupt:
            log("Stopped.")
    stats["module_bases"] = bases
    return stats


# --- Comparing ----------------------------------------------------------------


def read_state(path: Path) -> dict[int, dict]:
    if path.is_dir():
        path = path / "state.jsonl"
    frames = {}
    with path.open(encoding="utf-8") as f:
        for line in f:
            if line.strip():
                row = json.loads(line)
                frames[row["frame"]] = row["fields"]
    return frames


def diff(expected: dict[int, dict], actual: dict[int, dict], only=None) -> dict | None:
    """First frame where the two runs disagree, or None if every shared frame matches."""
    for key in sorted(expected):
        if key not in actual:
            if any(k > key for k in actual):
                return {"frame": key, "missing": True, "fields": {}}
            break
        want, got = expected[key], actual[key]
        names = only or sorted(set(want) | set(got))
        bad = {n: (want.get(n), got.get(n)) for n in names if want.get(n) != got.get(n)}
        if bad:
            return {"frame": key, "missing": False, "fields": bad}
    return None


# --- CLI ----------------------------------------------------------------------


def _cmd_check_disc(args) -> int:
    problems = check_disc(args.image)
    for p in problems:
        print(f"MISMATCH {p}")
    if not problems:
        print(f"{args.image.name}: Loader and Game modules match this repo's build.")
    return 1 if problems else 0


def _cmd_inputs(args) -> int:
    rec = p2m2.parse(args.file.read_bytes())
    print(f"{rec.emulator} | {rec.game} | author {rec.author!r} | {len(rec.frames)} frames")
    prev = None
    for i, (pad, _) in enumerate(rec.frames):
        if pad.raw != prev and (args.limit is None or i < args.limit):
            held = " ".join(sorted(pad.pressed)) or "-"
            print(f"{i:8} {held:32} L{pad.left_stick} R{pad.right_stick}")
        prev = pad.raw
    return 0


def _connect(args):
    from tools.pine import Pine

    return Pine(args.slot)


def _cmd_locate(args) -> int:
    with _connect(args) as pine:
        print(f"{pine.game_id()} {pine.title()} ({pine.status()})")
        for name, secs in locate_all(pine, load_modules()).items():
            found = ", ".join(f"{s}@{a:#x}" for s, a in secs.items()) or "not loaded"
            print(f"{name}: {found}")
    return 0


def _cmd_record(args) -> int:
    run = args.run
    run.mkdir(parents=True, exist_ok=True)
    manifest = {"schema": SCHEMA, "note": args.note, "start": args.start}
    if args.disc:
        problems = check_disc(args.disc)
        if problems:
            print("\n".join(problems), file=sys.stderr)
            return 1
        manifest["disc_image"] = {"name": args.disc.name, "sha1": sha1_file(args.disc)}
    if args.bios:
        manifest["bios"] = {"name": args.bios.name, "sha1": sha1_file(args.bios)}
    if args.memcard:
        manifest["memory_card"] = {"name": args.memcard.name, "sha1": sha1_tree(args.memcard)}
    shutil.copyfile(args.map, run / "state.toml")
    manifest["state_map_sha1"] = sha1_file(args.map)
    with _connect(args) as pine:
        manifest["pcsx2"] = pine.version()
        manifest["game"] = {"id": pine.game_id(), "title": pine.title()}
        manifest["started"] = time.strftime("%Y-%m-%dT%H:%M:%S%z")
        (run / "run.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
        print(f"Recording {manifest['game']['title']} into {run}. Ctrl+C stops.")
        manifest["recorded"] = record(pine, run, args.map, load_modules(), max_frames=args.frames)
    inputs = run / "inputs.p2m2"
    if inputs.is_file():
        manifest["input_frames"] = len(p2m2.parse(inputs.read_bytes()).frames)
    (run / "run.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    r = manifest["recorded"]
    print(f"{r['frames']} frames, {r['skipped']} skipped, {r['torn']} retries exhausted.")
    return 0


def _cmd_info(args) -> int:
    print(json.dumps(json.loads((args.run / "run.json").read_text(encoding="utf-8")), indent=2))
    return 0


def _cmd_diff(args) -> int:
    expected, actual = read_state(args.expected), read_state(args.actual)
    only = args.fields.split(",") if args.fields else None
    result = diff(expected, actual, only)
    shared = len(set(expected) & set(actual))
    if result is None:
        print(f"No divergence in {shared} shared frames.")
        return 0
    if result["missing"]:
        print(f"Frame {result['frame']} is missing from {args.actual}.")
    else:
        print(f"First divergence at frame {result['frame']}:")
        for name, (want, got) in result["fields"].items():
            print(f"  {name}: expected {want!r}, got {got!r}")
    return 1


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Record and compare Reference runs.")
    sub = parser.add_subparsers(dest="command", required=True)

    p = sub.add_parser("check-disc", help="check a Disc image against this repo's build")
    p.add_argument("image", type=Path)
    p.set_defaults(func=_cmd_check_disc)

    p = sub.add_parser("inputs", help="summarize a .p2m2 Input Recording")
    p.add_argument("file", type=Path)
    p.add_argument("--limit", type=int, help="only list changes before this frame")
    p.set_defaults(func=_cmd_inputs)

    for name, func, help_text in (
        ("locate", _cmd_locate, "show where the Game modules are loaded"),
        ("record", _cmd_record, "record game state from PCSX2 into a run folder"),
    ):
        p = sub.add_parser(name, help=help_text)
        p.add_argument("--slot", type=int, default=28011, help="PINE slot (PCSX2 setting)")
        p.set_defaults(func=func)
        if name == "record":
            p.add_argument("run", type=Path, help="run folder, e.g. refruns/new-game")
            p.add_argument("--map", type=Path, default=DEFAULT_MAP)
            p.add_argument("--disc", type=Path, help="Disc image, checked and hashed")
            p.add_argument("--bios", type=Path, help="BIOS file PCSX2 booted, hashed")
            p.add_argument("--memcard", type=Path, help="memory card file or folder used")
            p.add_argument("--start", default="power-on", help="start condition")
            p.add_argument("--note", default="")
            p.add_argument("--frames", type=int, help="stop after this many frames")

    p = sub.add_parser("info", help="print a run's manifest")
    p.add_argument("run", type=Path)
    p.set_defaults(func=_cmd_info)

    p = sub.add_parser("diff", help="find the first frame where two runs diverge")
    p.add_argument("expected", type=Path, help="run folder or state.jsonl")
    p.add_argument("actual", type=Path, help="run folder or state.jsonl")
    p.add_argument("--fields", help="comma-separated fields to compare")
    p.set_defaults(func=_cmd_diff)

    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
