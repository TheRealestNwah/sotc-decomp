/*
 * Reader for PCSX2 GS dumps (.gs), the frame captures PCSX2 writes with
 * Shift+F8. Format notes in docs/render-translator.md.
 *
 * A dump is a header (serial, CRC, a screenshot), a GS state freeze (registers
 * and the full 4 MiB VRAM), the privileged registers, then a packet stream of
 * GIF transfers per path and vsyncs. The reader works on a buffer the caller
 * keeps alive; nothing is copied. Compressed dumps (.gs.zst, .gs.xz) must be
 * decompressed first.
 */
#ifndef SOTC_PORT_RENDER_GSDUMP_H
#define SOTC_PORT_RENDER_GSDUMP_H

#include <stddef.h>
#include <stdint.h>

struct gs_dump {
    uint32_t crc;
    uint32_t state_version; /* 0 for old dumps without the extended header */
    const char *serial;     /* not NUL-terminated */
    size_t serial_size;
    uint32_t screenshot_width, screenshot_height;
    const uint8_t *screenshot; /* RGBA8 rows, or NULL */
    const uint8_t *state;      /* GS state freeze */
    size_t state_size;
    const uint8_t *privregs; /* GS_PRIV_SIZE bytes */
    const uint8_t *packets;  /* packet stream, to the end of the buffer */
    size_t packets_size;
};

enum gs_dump_packet_type {
    GS_DUMP_TRANSFER = 0,
    GS_DUMP_VSYNC = 1,
    GS_DUMP_READFIFO = 2,
    GS_DUMP_REGISTERS = 3
};

/* GIF paths as the dump numbers them (PCSX2's GSTransferPath). */
enum {
    GS_DUMP_PATH1_OLD = 0, /* PATH1 from older dumps; same data, replayed as PATH1 */
    GS_DUMP_PATH2 = 1,
    GS_DUMP_PATH3 = 2,
    GS_DUMP_PATH1 = 3
};

struct gs_dump_packet {
    int type;
    int path;            /* TRANSFER */
    const uint8_t *data; /* TRANSFER data, or REGISTERS block */
    uint32_t size;       /* TRANSFER/READFIFO size in bytes */
    int field;           /* VSYNC */
};

/* Parses the header. Returns 0, or -1 with *error set to a static message. */
int gs_dump_open(struct gs_dump *dump, const uint8_t *data, size_t size, const char **error);

/*
 * Reads the packet at *cursor (start at 0) and advances it.
 * Returns 1 for a packet, 0 at the end, -1 for a truncated or unknown packet.
 */
int gs_dump_next(const struct gs_dump *dump, size_t *cursor, struct gs_dump_packet *packet);

/* One drawing context's registers in a state freeze. */
struct gs_freeze_context {
    uint64_t xyoffset, tex0, tex1, clamp, miptbp1, miptbp2, scissor, alpha, test, fba, frame, zbuf;
};

/* The registers and VRAM of a GS state freeze. */
struct gs_freeze {
    uint32_t version;
    uint64_t prim, prmodecont, texclut, scanmsk, texa, fogcol, dimx, dthe, colclamp, pabe;
    uint64_t bitbltbuf, trxdir, trxpos, trxreg;
    struct gs_freeze_context ctx[2];
    uint64_t rgbaq, st, uv, fog, xyz;
    const uint8_t *vram; /* GS_VRAM_SIZE bytes inside the dump buffer */
    float q;
};

/*
 * Parses a state freeze. Registers come from the start (a layout every state
 * version since 6 shares) and VRAM from the end, which only depends on the
 * fixed-size GIF path block after it. Returns 0, or -1 if it is too small.
 */
int gs_freeze_parse(const uint8_t *state, size_t size, struct gs_freeze *freeze);

/* Recognises zstd and xz data; returns "zstd", "xz" or NULL. */
const char *gs_dump_compression(const uint8_t *data, size_t size);

#endif
