# sotc-decomp

Matching decompilation of Shadow of the Colossus (PS2, NTSC-U `SCUS-97472`), aiming for a later native PC port. See README.md for the roadmap.

## Commands

- Install: `pip install -r requirements.txt` (inside `.venv`)
- Test: `pytest`
- Lint: `ruff check .` and `ruff format --check .` (fix with `ruff format .`)
- Verify base executable: `python tools/check_baserom.py`

CI (`.github/workflows/ci.yml`) runs lint + tests on every PR.

## Layout

- `config/baserom.json`: expected executable name, path and SHA-1 (`sha1` is `null` until verified against a known-good dump)
- `tools/`: Python helper scripts; `tests/` covers them
- `src/`, `include/`: decompiled C code and headers (empty for now)

## Gotchas

- **Never commit game files.** `baserom/`, ELFs, ISOs and everything splat generates (`asm/`, `assets/`, `build/`) are gitignored. Keep it that way.
- The game is MIPS R5900 (Emotion Engine). Matching needs the original compiler version, which hasn't been identified yet.
- Don't fill in `sha1` in `config/baserom.json` from memory or the web without the user confirming it against their dump.
