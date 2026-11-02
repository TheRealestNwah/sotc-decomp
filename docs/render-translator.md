# Render translator prototype

The first piece of the Render translator ([ADR 0007](adr/0007-render-by-translating-the-games-packets.md)):
it reads a PCSX2 GS dump of the game, translates the GIF packets in it into
API-neutral draw batches, and draws them with a CPU reference backend so one
frame can be compared against PCSX2's own screenshot. Everything lives in
`port/render/`, with the `gsframe` tool in `port/tools/` and tests (synthetic
data only) in `port/tests/`.

```
GS dump --gsdump.c--> packets --gs_translate.c--> batches / transfers / vsync --gs_ref.c--> RGBA frame --gsframe--> PNG
```

The translator is the part the Native port keeps. The reference backend is a
test oracle and a stand-in until the SDL_GPU backend ([ADR 0009](adr/0009-sdl3-platform-library.md))
exists: it is a slow per-pixel loop, written for clarity over speed.

## Capturing a GS dump (needs the owner)

GS dumps hold frames of the game, so they stay local like everything else from
the disc (`*.gs`, `*.gs.zst` and `*.gs.xz` are gitignored; never commit one).

1. In PCSX2's graphics settings, set the GS dump compression to Uncompressed
   (`GSDumpCompression` in `PCSX2.ini`), or decompress afterwards with
   `zstd -d` or `xz -d`. `gsframe` refuses compressed dumps with a message
   saying which format it found.
2. Boot the game and get to a scene worth checking (the title screen first).
3. Press **Shift+F8** for a one-frame dump (Ctrl+Shift+F8 records several).
   PCSX2 writes it to its snapshots folder (`D:\Emulation\PCSX2\snaps` here).
4. Run it through the translator:

   ```
   build/port/gsframe snaps/<name>.gs -o frame.png --screenshot shot.png
   ```

   `frame.png` is what the Render translator drew; `shot.png` is the screenshot
   PCSX2 stored in the dump. `--frame N` stops at the Nth vsync instead of the
   first. The tool also prints counts (GIF tags per path, primitives by type,
   batches, transfers) and how often an approximation below was hit.

## Dump format

As written by PCSX2 1.7/2.x (`GSDump.cpp`), little-endian:

- **Header.** New dumps start with `0xFFFFFFFF`, then a header size and nine
  u32 fields: state version, state size, serial offset/size, CRC, screenshot
  width/height and offset/size. The serial and an RGBA screenshot follow in the
  header's extra bytes. Old dumps have no marker: just the CRC and state size.
- **Freeze state** (`state size` bytes): GS register state and the whole 4 MiB
  GS local memory, as PCSX2's GS freeze. `gsdump.c` reads the version, the
  per-context registers and the memory.
- **Privileged registers**: 0x2000 bytes (PMODE, DISPFB, DISPLAY, BGCOLOR...).
- **Packets**, each a type byte then data:
  - 0 transfer: path byte, u32 size, then GIF data. Path 0 is the old PATH1
    encoding, 1..3 are PATH2, PATH3 and PATH1 (mapped to GIF paths 2, 3, 1).
  - 1 vsync: one field byte.
  - 2 readfifo: u32 size (a readback; no data).
  - 3 registers: a fresh 0x2000-byte privileged register block.

## Translator design

`gs_translator` owns a copy of GS memory and the GS registers. It accepts GIF
data per path (`gs_translator_gif`), single register writes
(`gs_translator_write`) and vsyncs, and reports to a `gs_sink` with three
callbacks:

- **draw**: a `gs_batch`, which is a `gs_pipe` key plus a `gs_vertex` array.
  Consecutive primitives with byte-identical keys share one batch, so a backend
  can bind one pipeline per batch. Strips and fans are expanded to triangle
  lists and sprites to two triangles (6 vertices), so a batch is always plain
  triangles or plain lines.
- **transfer**: a finished host-to-local or local-to-local image transfer,
  already applied to the translator's GS memory. A backend uses it to drop or
  refresh any texture or render target that covers the rectangle.
- **vsync**: the privileged registers and GS memory, for presenting a frame.

The GIF front end handles PACKED (including A+D, ST/Q pairing, XYZF and the ADC
bit), REGLIST (with the odd-count padding qword) and IMAGE tags in every GS
storage mode, and keeps each path's state across packet boundaries, so a tag
split across two dump packets still decodes.

`gs_vertex` positions are in render-target pixels with XYOFFSET removed, and
texture coordinates are normalised and projective (sample at s/q, t/q), so
UV-mode (FST) and STQ primitives look the same to the backend.

`gs_blend_map` turns the GS blend equation `((A - B) * C >> 7) + D` into
fixed-function source and destination factors with an add, subtract or
reverse-subtract op, and says whether the mapping is exact.

## Reference backend

`gs_ref` keeps each render target and depth buffer as a linear image keyed by
its base page (FBP/ZBP), loaded from GS memory the first time it is drawn to.
It rasterises with Gouraud or flat colour, perspective
texturing (nearest or bilinear, clamp/repeat/region modes), all four texture
functions, fog, the alpha and depth tests, destination alpha test, the blend
above, the frame mask and colour clamping. A texture whose base matches a
render target is sampled from that target, which is how the game's
post-processing passes read back what it drew. A vsync composes the displayed
frame from PMODE, DISPFB and DISPLAY.

## Approximations and known gaps

Each of these is counted in `gsframe`'s output so a dump shows how much it
leans on them.

- **Blends with no fixed-function form.** When A equals D but B differs (for
  example `(Cs - Cd) * As + Cs`), the result has a (1 + C) factor no blend unit
  has; it is approximated and counted as `blend_approx`. A shader backend can
  do these exactly.
- **Alpha is scaled by 1/128**, so GS alpha above 0x80 would mean more than 1.0
  in a real GPU blend; the reference backend computes in floats and floors.
- **Partial frame masks** (not whole bytes) are applied per bit in the
  reference backend but have no fixed-function equivalent (`fbmsk_partial`).
- **No colour clamp** (COLCLAMP off, wrapping) is counted, not exact on GPUs.
- **CLUTs are read from GS memory at draw time** rather than from the GS's
  CLUT buffer, and CSA (the CLUT offset) is ignored. Games that reload the
  buffer between draws without rewriting memory would differ.
- **Mipmaps are ignored**: level 0 is always sampled (`mip_ignored`).
- **Render-target aliasing** is per base page only. A texture or target that
  overlaps another one at a different base sees GS memory, not the newer
  target (`rt_overlaps`).
- **No dithering, interlace or circuit merge**: the display reads circuit 1
  (or 2 if only it is on) and forces alpha to 0xFF.
- **PATH1 is translated as given.** A GS dump records what reached the GS,
  which already includes VU1's output, so this prototype does not run any VU1
  microprograms.

## Next steps

1. Capture a title-screen dump and compare `frame.png` with `shot.png`; fix
   what differs and add a synthetic test for each fix.
2. An SDL_GPU backend that draws `gs_batch` with real pipelines, using the
   `gs_pipe` key as the pipeline cache key and the reference backend as its
   test oracle. It needs SDL3 and a shader compiler, neither installed yet.
3. The VU1 side: hand-translate the game's VU1 microprogram overlay sets into C
   and check their output against the PATH1 packets in a dump, so the port can
   feed the translator from the Game code's own VIF packets instead of a dump.
