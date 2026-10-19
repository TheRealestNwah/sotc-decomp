# Shadow of the Colossus Decompilation

A work-in-progress decompilation of **Shadow of the Colossus** (PlayStation 2, NTSC-U, `SCUS-97472`), with the long-term goal of a native PC port.

The aim is C source that compiles back to a byte-identical copy of the original executable. Once that matches, the code can be ported to run natively on PC.

## Status

- The loader ELF `SCUS_974.72` splits with [splat](https://github.com/ethteck/splat) (1,038 functions) and **rebuilds byte-for-byte** from assembly (`ninja check` passes).
- The game code lives in the `.XFF` modules (custom `xff2` format, see [docs/xff2.md](docs/xff2.md)).
  - All three (`KERNEL`, `MANAGER`, `GAMECORE`) split into assembly that reassembles with every section and relocation matching the originals. That's about 70,000 relocations.
  - The modules keep their original symbol names.
- **All three `.XFF` files rebuild byte-for-byte**, including their headers and tables. Code/data and symbol locations come from the assembled objects; original table-layout and loader metadata are still supplied by the disc files (see [docs/xff2.md](docs/xff2.md)).
- **Compiler identified:** Sony `ee-gcc` 2.96, `-O2 -G0`.
- **3,942 functions are compiled from matching C** (2,146 GAMECORE, 1,266 MANAGER, 530 KERNEL), including most small getters and setters and the sword beam,
  weak-point glow and query, collision reaction, sound volume, particle emitter and reaction-thread updates. C in `src/xff/`
  is compiled and spliced into the modules; the full build still matches.
- The native PC port remains future work.

See [docs/findings.md](docs/findings.md) for what's known about the binaries, the compiler and the linked Sony SDK libraries.

## You need your own copy of the game

This repo contains **no original game binaries or assets**. Dump your own disc and copy `SCUS_974.72` into `iso/`. Never commit anything from the disc.

## Setup (Windows)

1. Install Python 3.11+.
2. Install the PS2DEV EE toolchain (`ps2dev-windows-latest.tar.gz` from the [ps2dev/ps2dev releases](https://github.com/ps2dev/ps2dev/releases)) and put its `ee\bin` folder on `PATH`. It also needs a 32-bit `libzstd.dll` (from the [zstd releases](https://github.com/facebook/zstd/releases), `win32` zip) copied into `ee\bin`.
3. Then:

```bash
python -m venv .venv
.venv\Scripts\pip install -r requirements.txt
.venv\Scripts\python tools/check_baserom.py
.venv\Scripts\python configure.py
.venv\Scripts\ninja check
```

## Roadmap

See [roadmap.md](roadmap.md) for completed milestones, remaining matching work,
the future native PC port and community proposals. Planned work before 1.0 is
tracked there; feature requests and discovered bugs still use GitHub issues.

## Layout

| Path | Purpose |
| --- | --- |
| `SCUS_974.72.yaml` | splat config for the loader ELF |
| `configure.py` | Generates `build.ninja` |
| `config/` | Expected original executable path and hash |
| `docs/` | Findings about the binaries and toolchain |
| `src/` | Matching C source for the XFF modules |
| `include/` | Assembler macros and headers |
| `tools/` | Helper scripts (ELF flattener, match checker) |
| `tests/` | Tests for the helper scripts |

## AI disclosure

This project is developed with [Claude Code](https://claude.com/claude-code),
Anthropic's AI coding assistant, and [OpenAI Codex](https://openai.com/codex/).
These assistants contribute code, tests and documentation. The
maintainer ([@TheRealestNwah](https://github.com/TheRealestNwah)) decided what
it should do, tested it, and made the release decisions. Commits written with
Claude carry a `Co-Authored-By: Claude` trailer. This disclosure also covers
Codex contributions.

## Support

Everything on my GitHub is free of charge and open source. If you find it
useful and want to leave a tip or buy me a coffee, you can do that at
[ko-fi.com/morrowheat23](https://ko-fi.com/morrowheat23). It's appreciated,
never expected.

## License

The code and tools in this repo are dedicated to the public domain under [CC0 1.0](LICENSE). This covers only the repo's own contents, never the game or anything derived from your disc.
