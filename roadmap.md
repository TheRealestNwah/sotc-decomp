# Roadmap

Last reviewed: 2026-11-17.

Planned work before 1.0 lives here. Keep this file current as plans change and
work lands. Community requests come in as feature-request issues on GitHub
and stay there; this roadmap can link to them when relevant. Discovered bugs
also get issues. Planned build tasks do not need individual issues. Unchecked items are future
work, not a release-date or feature commitment.

## Completed foundations

- [x] Verify the hash of the Original NTSC-U Loader.
- [x] Split the Loader with splat and rebuild its loaded bytes exactly.
- [x] Reverse the xff2 format and reproduce Game module sections and relocations.
- [x] Rebuild all three complete Game modules byte-for-byte, retaining original
  table-layout and loader metadata from the owner's disc.
- [x] Identify Sony ee-gcc 2.96 with `-O2 -G0` and its original assembler, and
  establish the matching-C compile, splice and verification workflow.
- [x] Run Python lint, format checks and synthetic tool tests in PR CI.

## The road to 1.0

1.0 is a playable Native port on Windows x64: a new game through all 16
colossi to the credits, with audio, saves and controller input, agreeing with
the gating Reference runs ([ADR 0019](docs/adr/0019-one-point-zero-is-a-playable-port.md)).
Two tracks run side by side: matching and Source cleanup (the default for
autonomous work), and Platform layer groundwork (when the owner asks for it).
See the [README](README.md#status) for Matched function counts and
[binary findings](docs/findings.md) for evidence. CI has no disc files or PS2
toolchain, so passing CI alone does not prove matching.

### M1: all Game code matched

Work goes Source group by Source group: the groups with the fewest unmatched
functions first, then the groups the port needs first to boot. Within a group,
Parked attempts with the fewest diffs come first. The full list of unmatched
functions is generated in [docs/unmatched.md](docs/unmatched.md) (refreshed
with the README progress table); the closed issues formerly listed here keep
their investigation notes, so search the issue tracker for a function's name
before retrying it.

- [ ] Report matched, parked and fresh counts per Source group in
  `docs/unmatched.md`, sorted in work order.
- [ ] Add the Handwritten asm class ([ADR 0017](docs/adr/0017-handwritten-asm-class.md)):
  `config/handwritten_asm.txt`, splice support and exclusion from the totals,
  starting with MANAGER `func_0001E9C0` and the Loader's `setCop0Epc`.
- [ ] Sort MANAGER's and GAMECORE's functions into SDK routines, Handwritten asm
  and Game code (`config/sdk_routines.txt`; MANAGER's `rand` and `srand` are identified).
- [ ] Match the Loader's remaining Game code. C data isn't supported by the
  Loader splice yet.
- [ ] Match the remaining Game code in KERNEL, MANAGER and GAMECORE, including
  their data, constants, original interfaces and Source groups.
- [x] Identify KERNEL's SDK routines by signature, and count only Game code in
  the README progress table ([#2285](https://github.com/TheRealestNwah/sotc-decomp/issues/2285)).
- [x] Sort the Loader's functions into SDK routines and Game code
  (`config/loader_functions.csv`, [ADR 0004](docs/adr/0004-finish-line-and-source-cleanup.md)).
- [x] Add a C build path for the Loader (`tools/loader_splice.py`, `src/loader/`,
  built with `-G8`).

Parked attempts (`NONMATCHING` C) stay uncounted until verified with the
original compiler and assembler, full local binary checks and passing PR CI.

### M2: Source cleanup

Starts per Source group as soon as the group is fully matched
([ADR 0004](docs/adr/0004-finish-line-and-source-cleanup.md)). One PR per group,
no matching changes mixed in, `ninja check` byte-identical.

- [ ] `include/common.h` with the base types.
- [ ] Merge each fully matched Source group into one C file with its own
  `include/<module>/<group>.h`; move structs to `include/<topic>.h` once two
  groups share them.
- [ ] Grow `config/refrun/state.toml` (game mode or scene, player and camera
  positions) as structs are decoded.
- [ ] Replace Placeholder names with descriptive ones as purposes become known
  (runs alongside the rest).

### M3: the port boots to the title screen

The port replays the boot-to-title Reference run, matching the state map frame
by frame, and its title-frame screenshot is visually close to PCSX2's. Floats
are compared with tolerances ([ADR 0018](docs/adr/0018-native-floats-compared-with-tolerances.md)).

### M4: the first colossus is playable

The port agrees with the new-game-to-first-colossus and first-fight Reference runs.

### M5: full playthrough (1.0)

The port agrees with all 20 gating Reference runs.

- [ ] Investigate original error-path contracts and address confirmed defects
  deliberately, with regression coverage. Current tracked concerns include the
  [sheet lookup missing-header read (#492)](https://github.com/TheRealestNwah/sotc-decomp/issues/492),
  [AI damage checks reading before a null guard (#490)](https://github.com/TheRealestNwah/sotc-decomp/issues/490),
  and [sequence stop using uncaptured interrupt state (#708)](https://github.com/TheRealestNwah/sotc-decomp/issues/708).
  Preserve exact original behavior during the matching phase.

## Native port

Decisions are recorded in [ADRs 0005 to 0019](docs/adr/). In short: one source
tree with a build macro, Windows x64 first, SDL3 and SDL_GPU, CMake and Clang,
SDK routines replaced by a Platform layer, a Render translator for the game's
GS packets and VU1 microprograms, the game's own Sound driver ported to C, saves
as memory card folders, EE threads as fibers, a 4 GB arena with 32-bit offset
pointers, native floats compared with tolerances, and Reference runs against
PCSX2 as the main check. Assets come from the owner's own Disc image; no
Original game binaries or assets are distributed. Scope is NTSC-U only for now,
and network and `host0` debug code is compiled out of the port.

### Platform layer groundwork

These don't compile the game's own C, so they run alongside matching
([ADR 0003](docs/adr/0003-match-everything-before-porting.md)). Next in order:
the runtime core, then the Render translator, then the Sound driver.

- [x] Owner dumps a full Disc image into `iso/` (needed for `NICO.DAT` and
  `SG2IOPM1.IRX`). Its executables match the NTSC-U hashes in
  [docs/findings.md](docs/findings.md).
- [x] Disc image reader and `NICO.DAT` archive parser, with asset-free tests on
  synthetic data (`port/disc/`, format in [docs/nicodat.md](docs/nicodat.md)).
- [x] Check the `NICO.DAT` header layout against the owner's Disc image with
  `nicoinfo`, and name the fields still marked unknown. The layout held; tex
  segs and special fs entries are now named. Kinds 3 and 4 of special fs key
  remain open (see the doc).
- [x] Reference run recording: capture inputs and per-frame game state from the
  Matching build in PCSX2 (`tools/refrun.py`, see `docs/reference-runs.md`).
- [ ] Owner records the inputs for the 20 gating Reference runs (checklist in
  [docs/reference-runs.md](docs/reference-runs.md#runs-that-gate-10)). State is re-recorded
  later from the same inputs as `config/refrun/state.toml` grows.
- [x] Render translator prototype fed from PCSX2 GS dumps: dump parser, GIF
  translator to API-neutral draw batches, and a CPU reference backend that
  draws one frame to a PNG (`port/render/`, `gsframe`; see
  [docs/render-translator.md](docs/render-translator.md)).
- [x] Check the Render translator against a real GS dump of the title screen:
  it matches PCSX2's screenshot once the dump is replayed 300 frames (the
  game's double-buffer copy and temporal sky glow need it; see
  docs/render-translator.md).
- [ ] Runtime core: the 4 GB memory arena ([ADR 0015](docs/adr/0015-game-memory-in-a-4gb-arena.md)),
  EE threads as fibers ([ADR 0014](docs/adr/0014-ee-threads-as-fibers.md)) and an SDL3 window
  and input ([ADR 0009](docs/adr/0009-sdl3-platform-library.md)), tested with synthetic data.
- [ ] SDL_GPU backend for the Render translator's draw batches, with the
  reference backend as its test oracle.
- [ ] Hand-translate the roughly 14 VU1 microprogram overlay sets into C and
  check their output against the PATH1 packets in GS dumps.
- [ ] Port the Sound driver to C ([ADR 0012](docs/adr/0012-audio-via-a-working-port-of-the-sound-driver.md)).

### After 1.0

- [ ] Linux, then macOS, then Port features.

The port ships as source only until 1.0. After that, prebuilt binaries may go
on GitHub Releases, each with the maintainer's explicit permission and never
with Original game files.

### Community proposals awaiting scope decisions

[Feature request #498](https://github.com/TheRealestNwah/sotc-decomp/issues/498)
asks for Xbox-style controls, keyboard/mouse input, improved textures and
anti-aliasing, FSR, uncapped frame rates, and a launcher section for patches and
mods. These are Port features, considered only after 1.0; they are not accepted 1.0
requirements.

A release or tag still requires explicit maintainer permission.
