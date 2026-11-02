/*
 * Reference backend for the Render translator: draws translated batches on
 * the CPU with the semantics a GPU backend would have, so the translator's
 * output can be checked without a GPU and turned into PNGs from a GS dump.
 *
 * Like a GPU backend, it keeps render targets and depth buffers as separate
 * linear images (keyed by their GS base address) instead of writing draws
 * back into GS memory, decodes textures from the translator's VRAM, and
 * blends with the fixed-function factors from the pipeline key. Where that
 * differs from the GS, the difference is what a GPU backend would also show.
 * See docs/render-translator.md for what it approximates.
 */
#ifndef SOTC_PORT_RENDER_GS_REF_H
#define SOTC_PORT_RENDER_GS_REF_H

#include <stdint.h>

#include "gs_translate.h"
#include "gs_vram.h"

#define GS_REF_TARGETS 16
#define GS_REF_TEXTURES 32

struct gs_ref_target {
    int used;
    uint32_t base; /* FBP or ZBP, in 2048-word pages */
    uint32_t fbw;  /* 64-pixel units (colour targets) */
    unsigned psm;
    int width, height;
    uint8_t *rgba; /* colour: RGBA8, alpha in GS units */
    uint32_t *z;   /* depth */
};

struct gs_ref_texture {
    int used;
    struct gs_tex_regs key;
    uint64_t generation;
    int width, height;
    uint8_t *rgba;
};

struct gs_ref_stats {
    uint64_t pixels, rt_textures, rt_overlaps, mip_ignored, bad_textures, rt_refreshes, unsupported_targets;
};

struct gs_ref {
    const uint8_t *vram;
    uint64_t generation; /* bumped by every transfer, invalidating cached textures */
    struct gs_ref_target colour[GS_REF_TARGETS], depth[GS_REF_TARGETS];
    struct gs_ref_texture textures[GS_REF_TEXTURES];
    int next_texture;

    /* The last displayed frame (updated at every vsync). */
    int frame_width, frame_height;
    uint8_t *frame; /* RGBA8, alpha 255 */
    uint64_t frames;

    struct gs_ref_stats stats;
};

/* vram is the translator's GS memory, read when textures are decoded. */
void gs_ref_init(struct gs_ref *ref, const uint8_t *vram);
void gs_ref_free(struct gs_ref *ref);

/* The sink to pass to gs_translator_init. */
struct gs_sink gs_ref_sink(struct gs_ref *ref);

void gs_ref_draw(struct gs_ref *ref, const struct gs_batch *batch);
void gs_ref_transfer(struct gs_ref *ref, const struct gs_transfer *transfer);

/* Builds the displayed frame from the privileged registers (PMODE, DISPFB, DISPLAY, SMODE2). */
void gs_ref_display(struct gs_ref *ref, const uint8_t *privregs);

/* Colour target at FRAME.FBP, or NULL if nothing has drawn there. */
const struct gs_ref_target *gs_ref_find_target(const struct gs_ref *ref, uint32_t fbp);

#endif
