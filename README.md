# Shadow of the Colossus Decompilation

A work-in-progress decompilation of **Shadow of the Colossus** (PlayStation 2, NTSC-U, `SCUS-97472`), with the long-term goal of a native PC port.

The aim is C source that compiles back to a byte-identical copy of the original executable. Once that matches, the code can be ported to run natively on PC.

## Status

Early setup. Nothing is split or decompiled yet.

## You need your own copy of the game

This repo contains **no game code, data or assets**. To work on it you need to dump your own legally owned disc and copy the executable (`SCUS_974.72`) into `baserom/`. Never commit anything from the disc.

## Setup

```bash
python -m venv .venv
.venv/Scripts/activate        # Windows; use .venv/bin/activate elsewhere
pip install -r requirements.txt
python tools/check_baserom.py
```

## Roadmap

1. Verify the base executable hash (`tools/check_baserom.py`)
2. Split the ELF into assembly and data with [splat](https://github.com/ethteck/splat)
3. Identify the original compiler (likely a version of the PS2 `ee-gcc`) and get a matching build
4. Decompile functions one at a time, using [decomp.me](https://decomp.me) to match them
5. Once fully matching, build a PC port layer (graphics, audio, input)

## Layout

| Path | Purpose |
| --- | --- |
| `config/` | Base executable metadata and (later) splat config |
| `src/` | Decompiled C source |
| `include/` | Headers |
| `tools/` | Helper scripts |
| `tests/` | Tests for the helper scripts |
