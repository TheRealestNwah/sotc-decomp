# Reference runs

A Reference run records the pad inputs and per-frame game state of the Matching
build running in PCSX2 ([ADR 0016](adr/0016-verify-the-port-with-reference-runs.md)).
The Native port replays the inputs and `tools/refrun.py diff` reports the first
frame where its state differs. Runs come from the owner's own disc, so they
live in `refruns/` (gitignored) and only run locally. CI covers the tools with
synthetic data.

## What a run holds

```
refruns/<name>/
  run.json      manifest
  inputs.p2m2   PCSX2 Input Recording, from power-on
  state.jsonl   one line per game frame
  state.toml    copy of the state map the run used
```

`run.json` records what's needed to reproduce the run and to tell two runs
apart: the Disc image's name and SHA-1 (after checking that its Loader and Game
modules match this repo), the BIOS and memory card hashes, the PCSX2 build,
the start condition, the state map's hash, frame counts and where the Loader put
each Game module section.

`state.jsonl` lines look like
`{"frame": 1234, "fields": {"main_call_counter": 617, "pad_manager_head": "ffff7f7f..."}}`.
Integers and floats are stored as JSON numbers (an `f32` round-trips exactly),
`bytes` fields as hex, arrays as lists.

### Inputs

PCSX2's own Input Recording is the input file. It stores both pads for every
vsync from the moment recording starts, and PCSX2 can play it back, which
makes a run re-checkable on a later PCSX2. `tools/p2m2.py` reads the format
(version 1, documented in its docstring) and `refrun inputs` prints the frames
where the pad changes. Runs start from power-on, never from a savestate: the
Native port can't load PCSX2 savestates, so a run that starts from one can't be
replayed. To skip ahead, start from a memory card save instead and pass the card
to `--memcard` so its hash is recorded.

### Game state

`config/refrun/state.toml` (the state map) lists what to read each frame. The
frame key is the vsync interrupt count that `getVIntrCnt` returns
(KERNEL `.data` + 0x7D4). It counts the same vsyncs the Input Recording counts,
and the Native port keeps the same counter, so both sides line rows up by it.
Fields name a Game module symbol, a section plus offset, or an absolute address
(the Loader is not relocated). Add fields as the port needs them; a new field
only affects runs recorded after it.

## How the recorder works

1. **Find the Game modules.** The Loader relocates `KERNEL.XFF`, `MANAGER.XFF`
   and `GAMECORE.XFF` at runtime, so symbol addresses aren't fixed. The recorder
   reads EE RAM over PINE and searches it for runs of `.text` words that no
   relocation touches (a run must appear exactly once). Every other section's
   base follows from relocated words in sections it has already found: a local
   `R_MIPS_32` site holds `saved word + section base + symbol value`, and a
   `HI16`/`LO16` pair holds the same sum split across two instructions. It waits
   until all three modules are loaded.
2. **Poll each frame.** One batched PINE request reads the frame key, every
   field, then the frame key again. PCSX2 answers memory reads without pausing
   emulation, so if the two keys differ the snapshot straddled a frame and is
   retried. A frame the recorder missed entirely is counted in `skipped`.
3. **Stop** on Ctrl+C, after `--frames`, or when the frame counter stops for 30
   seconds.

Run PCSX2 slowed down (for example 25% speed) so the recorder sees every frame.
Speed doesn't change what the game computes, only how often the recorder can
look.

## Recording a run

One-time PCSX2 setup:

- PCSX2 2.x (built against 2.7.81), with **Settings > Advanced > PINE
  Settings** enabled on slot 28011.
- A BIOS dumped from your own console. An NTSC-U one fits this game best.
- Turn off cheats and any widescreen or other game patches for Shadow of the
  Colossus: they change the game's code or data, so the run would no longer be
  of the Matching build. Keep PCSX2's game database fixes on; they're part of
  emulating the game correctly (for example it sets the EE FPU to round toward
  zero, which the Native port must reproduce too).
- No fast-forward, turbo or frame skipping while recording.
- For a new-game run, a freshly formatted memory card in slot 1, ideally a
  folder memory card ([ADR 0013](adr/0013-saves-as-memory-card-folders.md)).

Per run:

```
python -m tools.refrun check-disc <disc image>
```

1. In PCSX2, **Tools > Input Recording > New**, choose "Boot", and save to
   `refruns/<name>/inputs.p2m2`. PCSX2 boots the Disc image and starts recording.
2. Start the recorder, which waits for the game:
   ```
   python -m tools.refrun record refruns/<name> --disc <disc image> --bios <bios> --memcard <card> --note "new game to colossus 1"
   ```
3. Play. Stop the Input Recording in PCSX2, then Ctrl+C the recorder.
4. Check it with `python -m tools.refrun info refruns/<name>`. Recording the same
   inputs twice and diffing the two runs is a quick check that the setup is
   deterministic.

`python -m tools.refrun locate` shows where the Game modules are loaded right now,
which helps when adding fields.

## Comparing

```
python -m tools.refrun diff refruns/<expected> <actual run or state.jsonl> [--fields a,b]
```

It prints the first frame where any field differs (or where the second run is
missing a frame), with both values, and exits 1. A run that matches as far as it
goes exits 0.

## Known limits

- **Random numbers live in VU0.** `iosInitRandom`/`iosGetRandom` use the VU0
  `R` register (`vrinit`/`vrnext`/`vrxor`), which isn't in EE RAM and so can't be
  recorded. The Native port must reproduce `vrnext` bit for bit; a divergence
  that starts at a random roll points there.
- **Snapshots aren't atomic.** The before/after frame key check catches tearing
  across frames, not a field written partway through the game's own update in
  the same frame. Read fields the game finishes updating before vsync.
- **Input alignment.** The Input Recording counts frames from when recording
  starts (BIOS boot included) and the game counts vsyncs from when KERNEL
  starts. The offset between them is to be confirmed on the first real run, by
  matching the recorded pad data (`pad_manager_head`) to the Input Recording.
- PCSX2's PINE has no frame counter or pause-per-frame command, so the recorder
  can't step emulation; slowing PCSX2 down is what keeps it in step.
