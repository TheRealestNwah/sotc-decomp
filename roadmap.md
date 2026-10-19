# Roadmap

Last reviewed: 2026-10-18.

Planned work before 1.0 lives here. Keep this file current as plans change and
work lands. Community requests come in as feature-request issues on GitHub
and stay there; this roadmap can link to them when relevant. Discovered bugs
also get issues. Planned build tasks do not need individual issues. Unchecked items are future
work, not a release-date or feature commitment.

## Completed foundations

- [x] Verify the original NTSC-U executable hash.
- [x] Split the loader ELF with splat and rebuild its loaded bytes exactly.
- [x] Reverse the XFF module format and reproduce module sections and relocations.
- [x] Rebuild all three complete XFF files byte-for-byte, retaining original
  table-layout and loader metadata from the user's disc files.
- [x] Identify Sony ee-gcc 2.96 with `-O2 -G0` and its original assembler, and
  establish the matching-C compile, splice and verification workflow.
- [x] Run Python lint, format checks and synthetic tool tests in PR CI.

## Current phase: matching decompilation

The loader rebuilds from assembly; the game modules are only partly recovered
as matching C. The native PC port has not started. See the [README](README.md#status)
for merged function counts and [binary findings](docs/findings.md) for evidence.
CI has no disc files or PS2 toolchain, so passing CI alone does not prove matching.

- [ ] Recover the remaining game functions as matching C, including their data,
  constants, original interfaces and source-file groupings.
- [ ] Recover remaining loader code and identify linked Sony SDK routines by
  signature rather than decompiling library code by hand.
- [ ] Continue small sound-slot, sprite-menu, geometry, motion, ambient, weak-point
  fade and flag helper batches.
- [ ] Finish GAMECORE `sword.c`, including `nico_swordstart`, collision callbacks
  `T_000C1D80` / `T_000C2620`, and `DispWithSwordBlur` / `DispWithTorchBlur`.
- [ ] Match `GetStageContext` and `createWormCtrlWork` resource initialization.
- [ ] Match KERNEL `Sg2SmfpSetParam` and the timed pan/volume setters
  `Sg2SlotSetTimePanParam` / `Sg2SlotSetTimeVolParam`.
- [ ] Resolve register allocation for `nico_optBoneParentScaleUpdateScript`.
- [ ] Reach complete matching source coverage before starting the native port.

The remaining matching tasks above preserve the plans formerly tracked in
closed issues #18, #51, #52, #54, #55, #107, #208, #459, #460, #513 and #520.
Closing those planning issues did not mark their work complete. Parked
`NONMATCHING` attempts remain uncounted until independently verified with the
original compiler/assembler, full local binary checks and passing PR CI.

## Future phase: native PC port

- [ ] Build a native platform layer for graphics, audio and input after the
  matching decompilation is complete.
- [ ] Support loading the required assets from the user's own game copy; do not
  distribute original game binaries or assets.
- [ ] Investigate original error-path contracts before porting and address
  confirmed defects deliberately, with regression coverage. Current tracked
  concerns are the [sheet lookup missing-header read (#492)](https://github.com/TheRealestNwah/sotc-decomp/issues/492)
  and [AI damage checks reading before a null guard (#490)](https://github.com/TheRealestNwah/sotc-decomp/issues/490).
  Preserve exact original behavior during the matching phase.
- [ ] Define and validate supported platforms, packaging and runtime acceptance
  criteria before declaring a native 1.0 release ready.

### Community proposals awaiting scope decisions

[Feature request #498](https://github.com/TheRealestNwah/sotc-decomp/issues/498)
asks for Xbox-style controls, keyboard/mouse input, improved textures and
anti-aliasing, FSR, uncapped frame rates, and a launcher section for patches and
mods. These remain proposals to evaluate during port planning; they are not
accepted 1.0 requirements.

A release or tag still requires explicit maintainer permission.
