# 1.0 is a playable Native port, reached through five milestones

1.0 is a full playthrough on Windows x64: a new game through all 16 colossi to the credits, with audio, saves as memory card folders ([ADR 0013](0013-saves-as-memory-card-folders.md)) and controller input. It's accepted when the port agrees with a fixed set of Reference runs, with floats compared as [ADR 0018](0018-native-floats-compared-with-tolerances.md) describes:

- boot to the title screen;
- a new game through the intro to the first colossus;
- one run for each of the 16 colossus fights, each starting from a memory card save;
- a save and load cycle;
- a menu and options pass.

The milestones, in order:

- **M1** All Game code is matched, with SDK routines and Handwritten asm ([ADR 0017](0017-handwritten-asm-class.md)) classified.
- **M2** Source cleanup is finished: one C file per Source group and shared headers.
- **M3** The port boots to the title screen. It replays the boot-to-title Reference run, matching the state map frame by frame, and its title-frame screenshot is visually close to PCSX2's.
- **M4** The first colossus is playable.
- **M5** The full playthrough above. This is 1.0.

M2 overlaps M1 group by group ([ADR 0004](0004-finish-line-and-source-cleanup.md)), and platform-layer work feeds M3 ([ADR 0003](0003-match-everything-before-porting.md)). Port features such as widescreen, higher resolutions and uncapped frame rates come after 1.0: they change behavior and break comparison with Reference runs. Milestones are roadmap headings, not releases. Tags and releases still need the maintainer's explicit permission.

Defining 1.0 as the finished matching decomp was rejected: the project's goal is the port, and a 1.0 that stops short of it would mark the wrong finish line.
