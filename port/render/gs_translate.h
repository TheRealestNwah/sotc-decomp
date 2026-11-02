/*
 * The Render translator's GS front end (ADR 0007): consumes GIF packets as the
 * game sends them and turns them into API-neutral draw batches that a modern
 * GPU backend (SDL_GPU, ADR 0009) can submit directly.
 *
 * It is not a GS emulator. It tracks GS register state, assembles primitives
 * from vertex kicks, and describes each run of primitives that share render
 * state as one batch: a vertex array plus a pipeline key (target, depth,
 * blend, alpha test, texture). It owns a copy of GS local memory so image
 * transfers land where textures will later be sampled from; rendering itself,
 * including keeping render targets, is the backend's job.
 *
 * Design notes and what is approximated: docs/render-translator.md.
 */
#ifndef SOTC_PORT_RENDER_GS_TRANSLATE_H
#define SOTC_PORT_RENDER_GS_TRANSLATE_H

#include <stddef.h>
#include <stdint.h>

#include "gs_regs.h"

struct gs_dump_packet;
struct gs_freeze;

/*
 * A translated vertex. Positions are in render-target pixels with the
 * drawing offset removed. Texture coordinates are projective and
 * normalised: sample at (s/q, t/q) in [0,1] across the texture (TW, TH).
 * Colour and fog are raw GS values (alpha 0x80 means 1.0).
 */
struct gs_vertex {
    float x, y;
    uint32_t z;
    float s, t, q;
    uint8_t r, g, b, a;
    uint8_t fog;
    uint8_t pad[3];
};

enum gs_topology { GS_TOPOLOGY_TRIANGLES = 0, GS_TOPOLOGY_LINES = 1 };

/* Compare functions, shared by depth and alpha tests. */
enum gs_compare {
    GS_CMP_NEVER,
    GS_CMP_ALWAYS,
    GS_CMP_LESS,
    GS_CMP_LEQUAL,
    GS_CMP_EQUAL,
    GS_CMP_GEQUAL,
    GS_CMP_GREATER,
    GS_CMP_NOTEQUAL
};

/* Blend factors; C is the GS ALPHA.C operand, chosen by gs_blend.c_source. */
enum gs_blend_factor { GS_BF_ZERO, GS_BF_ONE, GS_BF_C, GS_BF_ONE_MINUS_C };

enum gs_blend_source { GS_BC_SRC_ALPHA, GS_BC_DST_ALPHA, GS_BC_CONSTANT };

/* result = src * src_factor  op  dst * dst_factor */
enum gs_blend_op { GS_BO_ADD, GS_BO_SUBTRACT, GS_BO_REVERSE_SUBTRACT };

struct gs_blend {
    uint8_t enable;
    uint8_t src, dst; /* enum gs_blend_factor */
    uint8_t op;       /* enum gs_blend_op */
    uint8_t c_source; /* enum gs_blend_source; alpha is scaled so 0x80 = 1.0 */
    uint8_t fix;      /* ALPHA.FIX for GS_BC_CONSTANT */
    uint8_t exact;    /* 0 when the GS equation had no fixed-function form and this approximates it */
    uint8_t pad;
};

/*
 * Maps an ALPHA register, ((A - B) * C >> 7) + D, to a fixed-function blend.
 * Returns 1 if exact, 0 if approximated (A == D with B != A gives (1 + C)
 * terms no blend unit has).
 */
int gs_blend_map(uint64_t alpha, struct gs_blend *out);

/* Texture function (TEX0.TFX). */
enum gs_tfx { GS_TFX_MODULATE, GS_TFX_DECAL, GS_TFX_HIGHLIGHT, GS_TFX_HIGHLIGHT2 };

/*
 * Everything a draw needs besides its vertices. Two batches with equal keys
 * (byte-wise; unused fields are zeroed) can be drawn with one pipeline and
 * one set of bindings.
 */
struct gs_pipe {
    /* Texture registers, raw; zero unless tme. */
    uint64_t tex0, tex1, clamp, texa, texclut;
    uint32_t fbmsk;   /* FRAME.FBMSK: 1 bits are not written */
    uint32_t fogcol;  /* FOGCOL, when fge */
    uint16_t scissor[4]; /* x0, x1, y0, y1, inclusive */
    uint16_t fbp, zbp;   /* FRAME.FBP and ZBUF.ZBP, in 2048-word pages */
    uint8_t topology;    /* enum gs_topology */
    uint8_t fbw;         /* FRAME.FBW, 64-pixel units */
    uint8_t fpsm, zpsm;
    uint8_t ztest;  /* enum gs_compare; GS keeps larger Z nearer */
    uint8_t zwrite;
    uint8_t atest, aref, afail; /* enum gs_compare, TEST.AREF, TEST.AFAIL */
    uint8_t date, datm;
    uint8_t tme, tfx, tcc, fge;
    uint8_t pabe, colclamp, fba, dthe;
    uint8_t pad;
    struct gs_blend blend;
};

struct gs_batch {
    const struct gs_pipe *pipe;
    const struct gs_vertex *vertices;
    uint32_t count;      /* vertices: 3 per triangle, 2 per line */
    uint32_t primitives; /* GS primitives (a sprite counts once) */
};

/* A finished host->local or local->local transfer, already applied to VRAM. */
struct gs_transfer {
    int local; /* 0 host->local, 1 local->local */
    uint32_t dbp, dbw, dpsm;
    int x, y, w, h; /* destination rectangle in pixels */
};

struct gs_display {
    const uint8_t *privregs; /* GS_PRIV_SIZE bytes */
    int field;
};

/* Callbacks the translator reports to; any of them may be NULL. */
struct gs_sink {
    void *user;
    void (*draw)(void *user, const struct gs_batch *batch);
    void (*transfer)(void *user, const struct gs_transfer *transfer, const uint8_t *vram);
    void (*vsync)(void *user, const struct gs_display *display, const uint8_t *vram);
};

struct gs_stats {
    uint64_t qwords[4]; /* per GIF path, 1..3 (index 0 unused) */
    uint64_t gif_tags, gif_tags_by_flg[4];
    uint64_t primitives[8], vertices, vertices_no_kick;
    uint64_t batches, batch_vertices;
    uint64_t transfers_host, transfers_local, transfers_readback, transfer_bytes;
    uint64_t blend_approx;   /* primitives drawn with an approximated blend */
    uint64_t fbmsk_partial;  /* ... with a frame mask that isn't whole bytes */
    uint64_t colclamp_off;   /* ... with colour wrapping instead of clamping */
    uint64_t unknown_regs, unknown_psm_transfers, vsyncs;
};

#define GS_PATHS 4
#define GS_BATCH_MAX_VERTICES 65535u

struct gs_gif_path {
    uint64_t regs;   /* REGS field of the current tag */
    uint32_t nloop;  /* loops left; 0 means the next qword is a tag */
    uint32_t nreg, reg, flg;
    uint8_t partial[16];
    uint32_t partial_size;
};

struct gs_translator {
    uint8_t *vram; /* GS_VRAM_SIZE bytes, owned */
    uint8_t privregs[GS_PRIV_SIZE];
    uint64_t regs[GS_REG_COUNT];
    uint32_t q_bits; /* Q from the last PACKED ST, applied by the next RGBAQ */

    struct gs_vertex queue[3];
    int queued;

    struct gs_gif_path path[GS_PATHS];

    struct {
        int active;
        uint32_t dbp, dbw, dpsm;
        int x0, y0, w, h, x, y;
        uint32_t acc, acc_bytes;
    } image;

    struct gs_pipe batch_pipe;
    struct gs_vertex *batch;
    uint32_t batch_count, batch_prims;

    struct gs_sink sink;
    struct gs_stats stats;
};

/* Returns 0, or -1 if out of memory. Starts with zeroed VRAM and registers. */
int gs_translator_init(struct gs_translator *t, const struct gs_sink *sink);
void gs_translator_free(struct gs_translator *t);

/* Loads registers and VRAM from a dump's state freeze and privileged registers. */
void gs_translator_load(struct gs_translator *t, const struct gs_freeze *freeze, const uint8_t *privregs);

/* Feeds GIF data for a path (1, 2 or 3). Tags may span calls. */
void gs_translator_gif(struct gs_translator *t, int path, const uint8_t *data, size_t size);

/* Writes one GS register as an A+D write would. */
void gs_translator_write(struct gs_translator *t, uint32_t reg, uint64_t value);

/* Ends a frame: flushes pending draws and reports the display. */
void gs_translator_vsync(struct gs_translator *t, int field);

/* Flushes the pending batch, if any. */
void gs_translator_flush(struct gs_translator *t);

/* Feeds one dump packet. Returns 1 if it was a vsync. */
int gs_translator_packet(struct gs_translator *t, const struct gs_dump_packet *packet);

#endif
