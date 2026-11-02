#include "gs_ref.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Render targets cover the whole height a 2048-word-page FBW buffer can address in practice. */
#define TARGET_HEIGHT 1024

/* TEXA that keeps a target's stored alpha: CT24 reads 0, CT16's A bit reads 0x80. */
#define RAW_TEXA (0x80ull << 32)

static int clampi(int v, int lo, int hi)
{
    return v < lo ? lo : v > hi ? hi : v;
}

void gs_ref_init(struct gs_ref *ref, const uint8_t *vram)
{
    memset(ref, 0, sizeof(*ref));
    ref->vram = vram;
}

static void free_texture(struct gs_ref_texture *t)
{
    free(t->rgba);
    memset(t, 0, sizeof(*t));
}

void gs_ref_free(struct gs_ref *ref)
{
    for (int i = 0; i < GS_REF_TARGETS; i++) {
        free(ref->colour[i].rgba);
        free(ref->depth[i].z);
    }
    for (int i = 0; i < GS_REF_TEXTURES; i++)
        free_texture(&ref->textures[i]);
    free(ref->frame);
    memset(ref, 0, sizeof(*ref));
}

static int is_colour_psm(unsigned psm)
{
    return psm == GS_PSMCT32 || psm == GS_PSMCT24 || psm == GS_PSMCT16 || psm == GS_PSMCT16S;
}

const struct gs_ref_target *gs_ref_find_target(const struct gs_ref *ref, uint32_t fbp)
{
    for (int i = 0; i < GS_REF_TARGETS; i++)
        if (ref->colour[i].used && ref->colour[i].base == fbp)
            return &ref->colour[i];
    return NULL;
}

/* Fills a rectangle of a colour target from GS memory. */
static void load_target_rect(struct gs_ref *ref, struct gs_ref_target *rt, int x0, int y0, int w, int h)
{
    for (int y = y0; y < y0 + h && y < rt->height; y++)
        for (int x = x0; x < x0 + w && x < rt->width; x++) {
            uint32_t v = gs_vram_read(ref->vram, rt->base * 32, rt->fbw, rt->psm, x, y);
            uint32_t c = gs_color_to_rgba(rt->psm, v, RAW_TEXA);
            memcpy(rt->rgba + ((size_t)y * rt->width + x) * 4, &c, 4);
        }
}

/*
 * The colour target for FRAME (FBP, FBW, PSM). The first draw to an address
 * creates it from what GS memory holds there, as a GPU backend would upload
 * it once; after that draws only touch the target.
 */
static struct gs_ref_target *colour_target(struct gs_ref *ref, uint32_t fbp, uint32_t fbw, unsigned psm)
{
    struct gs_ref_target *free_slot = NULL;
    for (int i = 0; i < GS_REF_TARGETS; i++) {
        struct gs_ref_target *rt = &ref->colour[i];
        if (rt->used && rt->base == fbp && rt->fbw == fbw) {
            rt->psm = psm;
            return rt;
        }
        if (!rt->used && !free_slot)
            free_slot = rt;
    }
    if (!free_slot || fbw == 0)
        return NULL;
    struct gs_ref_target *rt = free_slot;
    rt->width = (int)fbw * 64;
    rt->height = TARGET_HEIGHT;
    rt->rgba = calloc((size_t)rt->width * rt->height, 4);
    if (!rt->rgba)
        return NULL;
    rt->used = 1;
    rt->base = fbp;
    rt->fbw = fbw;
    rt->psm = psm;
    load_target_rect(ref, rt, 0, 0, rt->width, rt->height);
    return rt;
}

static struct gs_ref_target *depth_target(struct gs_ref *ref, uint32_t zbp, unsigned zpsm, uint32_t fbw)
{
    struct gs_ref_target *free_slot = NULL;
    for (int i = 0; i < GS_REF_TARGETS; i++) {
        struct gs_ref_target *d = &ref->depth[i];
        if (d->used && d->base == zbp && d->fbw == fbw)
            return d;
        if (!d->used && !free_slot)
            free_slot = d;
    }
    if (!free_slot || fbw == 0)
        return NULL;
    struct gs_ref_target *d = free_slot;
    d->width = (int)fbw * 64;
    d->height = TARGET_HEIGHT;
    d->z = calloc((size_t)d->width * d->height, sizeof(*d->z));
    if (!d->z)
        return NULL;
    d->used = 1;
    d->base = zbp;
    d->fbw = fbw;
    d->psm = zpsm;
    for (int y = 0; y < d->height; y++)
        for (int x = 0; x < d->width; x++)
            d->z[(size_t)y * d->width + x] = gs_vram_read(ref->vram, zbp * 32, fbw, zpsm, x, y);
    return d;
}

/* ---- textures ---- */

struct texture_view {
    const uint8_t *rgba; /* raw-alpha RGBA8 */
    int width, height, stride;
    unsigned psm; /* for CT24/CT16 alpha expansion when sampling a target */
    uint64_t texa;
    int from_target;
};

static int texture_view(struct gs_ref *ref, const struct gs_pipe *p, struct texture_view *v)
{
    uint32_t tbp = GS_FIELD(p->tex0, 0, 14), tbw = GS_FIELD(p->tex0, 14, 6);
    unsigned psm = GS_FIELD(p->tex0, 20, 6);
    memset(v, 0, sizeof(*v));
    gs_tex_size(p->tex0, &v->width, &v->height);

    /* Sampling what an earlier draw rendered: read the target, not stale GS memory. */
    for (int i = 0; i < GS_REF_TARGETS; i++) {
        const struct gs_ref_target *rt = &ref->colour[i];
        if (!rt->used)
            continue;
        uint32_t rt_start = rt->base * 32, rt_end = rt_start + (uint32_t)rt->fbw * (TARGET_HEIGHT / 32) * 32;
        if (tbp == rt_start && tbw == rt->fbw && is_colour_psm(psm)) {
            ref->stats.rt_textures++;
            v->rgba = rt->rgba;
            v->stride = rt->width;
            v->psm = psm;
            v->texa = p->texa;
            v->from_target = 1;
            if (v->width > rt->width)
                v->width = rt->width;
            if (v->height > rt->height)
                v->height = rt->height;
            return 0;
        }
        if (tbp >= rt_start && tbp < rt_end)
            ref->stats.rt_overlaps++;
    }

    struct gs_tex_regs key = { p->tex0, p->texa, p->texclut };
    for (int i = 0; i < GS_REF_TEXTURES; i++) {
        struct gs_ref_texture *t = &ref->textures[i];
        if (t->used && t->generation == ref->generation && memcmp(&t->key, &key, sizeof(key)) == 0) {
            v->rgba = t->rgba;
            v->stride = t->width;
            return 0;
        }
    }
    struct gs_ref_texture *t = &ref->textures[ref->next_texture];
    ref->next_texture = (ref->next_texture + 1) % GS_REF_TEXTURES;
    free_texture(t);
    t->rgba = malloc((size_t)v->width * v->height * 4);
    if (!t->rgba || gs_decode_texture(ref->vram, &key, t->rgba) != 0) {
        free_texture(t);
        ref->stats.bad_textures++;
        return -1;
    }
    t->used = 1;
    t->key = key;
    t->generation = ref->generation;
    t->width = v->width;
    t->height = v->height;
    v->rgba = t->rgba;
    v->stride = t->width;
    return 0;
}

/* Applies CLAMP's wrap mode to one integer texel coordinate. */
static int wrap(int c, int size, unsigned mode, int minv, int maxv)
{
    switch (mode) {
    case 0: /* REPEAT */
        return c & (size - 1);
    case 1: /* CLAMP */
        return clampi(c, 0, size - 1);
    case 2: /* REGION_CLAMP */
        return clampi(c, minv, maxv);
    default: /* REGION_REPEAT: MINU is a mask, MAXU a fixed part */
        return (c & minv) | maxv;
    }
}

static void texel(const struct texture_view *v, const struct gs_pipe *p, int u, int t, uint8_t out[4])
{
    uint64_t c = p->clamp;
    u = wrap(u, v->width, GS_FIELD(c, 0, 2), (int)GS_FIELD(c, 4, 10), (int)GS_FIELD(c, 14, 10));
    t = wrap(t, v->height, GS_FIELD(c, 2, 2), (int)GS_FIELD(c, 24, 10), (int)GS_FIELD(c, 34, 10));
    u = clampi(u, 0, v->width - 1);
    t = clampi(t, 0, v->height - 1);
    memcpy(out, v->rgba + ((size_t)t * v->stride + u) * 4, 4);
    if (v->from_target && v->psm != GS_PSMCT32) {
        /* Targets keep the stored alpha; expand it through TEXA as a texture read would. */
        uint32_t ta0 = GS_FIELD(v->texa, 0, 8), ta1 = GS_FIELD(v->texa, 32, 8);
        int aem = (int)GS_FIELD(v->texa, 15, 1);
        int black = out[0] == 0 && out[1] == 0 && out[2] == 0;
        if (v->psm == GS_PSMCT24)
            out[3] = (uint8_t)((aem && black) ? 0 : ta0);
        else
            out[3] = (uint8_t)(out[3] & 0x80 ? ta1 : (aem && black) ? 0 : ta0);
    }
}

static void sample(const struct texture_view *v, const struct gs_pipe *p, float s, float t, uint8_t out[4])
{
    float u = s * (float)v->width, w = t * (float)v->height;
    if (!GS_FIELD(p->tex1, 5, 1)) {
        texel(v, p, (int)floorf(u), (int)floorf(w), out);
        return;
    }
    /* Bilinear: texel centres sit at half-integer coordinates. */
    u -= 0.5f;
    w -= 0.5f;
    int u0 = (int)floorf(u), w0 = (int)floorf(w);
    float fu = u - (float)u0, fw = w - (float)w0;
    uint8_t c[4][4];
    texel(v, p, u0, w0, c[0]);
    texel(v, p, u0 + 1, w0, c[1]);
    texel(v, p, u0, w0 + 1, c[2]);
    texel(v, p, u0 + 1, w0 + 1, c[3]);
    for (int i = 0; i < 4; i++) {
        float top = c[0][i] + (c[1][i] - c[0][i]) * fu, bottom = c[2][i] + (c[3][i] - c[2][i]) * fu;
        out[i] = (uint8_t)clampi((int)lrintf(top + (bottom - top) * fw), 0, 255);
    }
}

/* ---- per-pixel pipeline ---- */

struct draw_ctx {
    struct gs_ref *ref;
    const struct gs_pipe *p;
    struct gs_ref_target *rt, *zt;
    struct texture_view tex;
    int has_tex;
    uint32_t zmax;
};

static int compare(unsigned fn, uint32_t a, uint32_t b)
{
    switch (fn) {
    case GS_CMP_NEVER:
        return 0;
    case GS_CMP_ALWAYS:
        return 1;
    case GS_CMP_LESS:
        return a < b;
    case GS_CMP_LEQUAL:
        return a <= b;
    case GS_CMP_EQUAL:
        return a == b;
    case GS_CMP_GEQUAL:
        return a >= b;
    case GS_CMP_GREATER:
        return a > b;
    default:
        return a != b;
    }
}

static float blend_factor(unsigned f, float c)
{
    switch (f) {
    case GS_BF_ZERO:
        return 0.0f;
    case GS_BF_ONE:
        return 1.0f;
    case GS_BF_C:
        return c;
    default:
        return 1.0f - c;
    }
}

/* One fragment: colour (r, g, b, a in GS units), depth, fog. */
static void shade(struct draw_ctx *d, int x, int y, const float col[4], double z, float fog, float s, float t, float q)
{
    const struct gs_pipe *p = d->p;
    struct gs_ref_target *rt = d->rt;
    if (x < p->scissor[0] || x > p->scissor[1] || y < p->scissor[2] || y > p->scissor[3])
        return;
    if (x < 0 || y < 0 || x >= rt->width || y >= rt->height)
        return;

    int c[4];
    for (int i = 0; i < 4; i++)
        c[i] = clampi((int)lrintf(col[i]), 0, 255);

    if (d->has_tex) {
        uint8_t tx[4];
        float iq = q != 0.0f ? 1.0f / q : 0.0f;
        sample(&d->tex, p, s * iq, t * iq, tx);
        int a = c[3];
        switch (p->tfx) {
        case GS_TFX_MODULATE:
            for (int i = 0; i < 3; i++)
                c[i] = clampi((c[i] * tx[i]) >> 7, 0, 255);
            c[3] = p->tcc ? clampi((a * tx[3]) >> 7, 0, 255) : a;
            break;
        case GS_TFX_DECAL:
            for (int i = 0; i < 3; i++)
                c[i] = tx[i];
            c[3] = p->tcc ? tx[3] : a;
            break;
        case GS_TFX_HIGHLIGHT:
        case GS_TFX_HIGHLIGHT2:
            for (int i = 0; i < 3; i++)
                c[i] = clampi(((c[i] * tx[i]) >> 7) + a, 0, 255);
            c[3] = p->tcc ? (p->tfx == GS_TFX_HIGHLIGHT ? clampi(a + tx[3], 0, 255) : tx[3]) : a;
            break;
        }
    }

    if (p->fge) {
        int f = clampi((int)lrintf(fog), 0, 255);
        for (int i = 0; i < 3; i++) {
            int fc = (int)GS_FIELD(p->fogcol, 8 * i, 8);
            c[i] = (f * c[i] + (255 - f) * fc) >> 8;
        }
    }

    int write_rgb = 1, write_a = 1, write_z = p->zwrite;
    if (!compare(p->atest, (uint32_t)c[3], p->aref)) {
        switch (p->afail) {
        case 0: /* KEEP */
            return;
        case 1: /* FB_ONLY */
            write_z = 0;
            break;
        case 2: /* ZB_ONLY */
            write_rgb = write_a = 0;
            break;
        default: /* RGB_ONLY */
            write_a = 0;
            write_z = 0;
            break;
        }
    }

    uint8_t *dst = rt->rgba + ((size_t)y * rt->width + x) * 4;
    if (p->date && ((dst[3] >> 7) & 1) != p->datm)
        return;

    if (d->zt) {
        uint32_t *zp = &d->zt->z[(size_t)y * d->zt->width + x];
        uint32_t zi = z <= 0 ? 0 : z >= (double)d->zmax ? d->zmax : (uint32_t)z;
        if (!compare(p->ztest, zi, *zp))
            return;
        if (write_z)
            *zp = zi;
    }
    if (!write_rgb && !write_a)
        return;

    if (p->blend.enable && (!p->pabe || c[3] >= 0x80)) {
        float cf;
        switch (p->blend.c_source) {
        case GS_BC_SRC_ALPHA:
            cf = (float)c[3] / 128.0f;
            break;
        case GS_BC_DST_ALPHA:
            cf = (float)dst[3] / 128.0f;
            break;
        default:
            cf = (float)p->blend.fix / 128.0f;
            break;
        }
        float fs = blend_factor(p->blend.src, cf), fd = blend_factor(p->blend.dst, cf);
        for (int i = 0; i < 3; i++) {
            float sv = (float)c[i] * fs, dv = (float)dst[i] * fd;
            float r = p->blend.op == GS_BO_ADD ? sv + dv : p->blend.op == GS_BO_SUBTRACT ? sv - dv : dv - sv;
            int ri = (int)floorf(r);
            c[i] = p->colclamp ? clampi(ri, 0, 255) : (ri & 0xFF);
        }
    }

    if (p->fba)
        c[3] |= 0x80;
    if (p->fpsm == GS_PSMCT16 || p->fpsm == GS_PSMCT16S) {
        for (int i = 0; i < 3; i++)
            c[i] &= 0xF8;
        c[3] = c[3] & 0x80 ? 0x80 : 0;
    }

    uint32_t old, nv = (uint32_t)c[0] | (uint32_t)c[1] << 8 | (uint32_t)c[2] << 16 | (uint32_t)c[3] << 24;
    memcpy(&old, dst, 4);
    uint32_t keep = p->fbmsk;
    if (!write_rgb)
        keep |= 0x00FFFFFF;
    if (!write_a || p->fpsm == GS_PSMCT24)
        keep |= 0xFF000000u;
    nv = (old & keep) | (nv & ~keep);
    memcpy(dst, &nv, 4);
    d->ref->stats.pixels++;
}

static int64_t fixed(float v)
{
    return (int64_t)llrintf(v * 16.0f);
}

static int64_t edge(int64_t ax, int64_t ay, int64_t bx, int64_t by, int64_t px, int64_t py)
{
    return (bx - ax) * (py - ay) - (by - ay) * (px - ax);
}

static int top_left(int64_t ax, int64_t ay, int64_t bx, int64_t by)
{
    return (by == ay && bx > ax) || by < ay;
}

static void attrs(const struct gs_vertex *v, float out[9])
{
    out[0] = v->r;
    out[1] = v->g;
    out[2] = v->b;
    out[3] = v->a;
    out[4] = (float)v->z;
    out[5] = v->fog;
    out[6] = v->s;
    out[7] = v->t;
    out[8] = v->q;
}

static void triangle(struct draw_ctx *d, const struct gs_vertex *v0, const struct gs_vertex *v1,
    const struct gs_vertex *v2)
{
    int64_t x0 = fixed(v0->x), y0 = fixed(v0->y), x1 = fixed(v1->x), y1 = fixed(v1->y), x2 = fixed(v2->x),
            y2 = fixed(v2->y);
    int64_t area = edge(x0, y0, x1, y1, x2, y2);
    if (area == 0)
        return;
    if (area < 0) {
        const struct gs_vertex *tv = v1;
        v1 = v2;
        v2 = tv;
        int64_t tx = x1, ty = y1;
        x1 = x2, y1 = y2, x2 = tx, y2 = ty;
        area = -area;
    }
    /* Positions as doubles keep Z (up to 32 bits) exact enough. */
    float a0[9], a1[9], a2[9];
    attrs(v0, a0);
    attrs(v1, a1);
    attrs(v2, a2);
    double z0 = v0->z, z1 = v1->z, z2 = v2->z;

    int64_t minx = x0 < x1 ? (x0 < x2 ? x0 : x2) : (x1 < x2 ? x1 : x2);
    int64_t maxx = x0 > x1 ? (x0 > x2 ? x0 : x2) : (x1 > x2 ? x1 : x2);
    int64_t miny = y0 < y1 ? (y0 < y2 ? y0 : y2) : (y1 < y2 ? y1 : y2);
    int64_t maxy = y0 > y1 ? (y0 > y2 ? y0 : y2) : (y1 > y2 ? y1 : y2);
    int px0 = clampi((int)((minx + 15) >> 4), d->p->scissor[0], d->p->scissor[1]);
    int px1 = clampi((int)(maxx >> 4), d->p->scissor[0], d->p->scissor[1]);
    int py0 = clampi((int)((miny + 15) >> 4), d->p->scissor[2], d->p->scissor[3]);
    int py1 = clampi((int)(maxy >> 4), d->p->scissor[2], d->p->scissor[3]);
    int b0 = top_left(x1, y1, x2, y2) ? 0 : 1, b1 = top_left(x2, y2, x0, y0) ? 0 : 1,
        b2 = top_left(x0, y0, x1, y1) ? 0 : 1;

    for (int py = py0; py <= py1; py++)
        for (int px = px0; px <= px1; px++) {
            int64_t sx = (int64_t)px * 16, sy = (int64_t)py * 16;
            int64_t w0 = edge(x1, y1, x2, y2, sx, sy), w1 = edge(x2, y2, x0, y0, sx, sy),
                    w2 = edge(x0, y0, x1, y1, sx, sy);
            if (w0 < b0 || w1 < b1 || w2 < b2)
                continue;
            double l0 = (double)w0 / (double)area, l1 = (double)w1 / (double)area, l2 = (double)w2 / (double)area;
            float a[9];
            for (int i = 0; i < 9; i++)
                a[i] = (float)(a0[i] * l0 + a1[i] * l1 + a2[i] * l2);
            shade(d, px, py, a, z0 * l0 + z1 * l1 + z2 * l2, a[5], a[6], a[7], a[8]);
        }
}

static void line(struct draw_ctx *d, const struct gs_vertex *v0, const struct gs_vertex *v1)
{
    float dx = v1->x - v0->x, dy = v1->y - v0->y;
    int steps = (int)ceilf(fmaxf(fabsf(dx), fabsf(dy)));
    float a0[9], a1[9];
    attrs(v0, a0);
    attrs(v1, a1);
    /* GS lines leave out the last pixel, like a GPU's diamond-exit rule. */
    for (int i = 0; i < steps; i++) {
        float f = (float)i / (float)steps, a[9];
        for (int k = 0; k < 9; k++)
            a[k] = a0[k] + (a1[k] - a0[k]) * f;
        double z = (double)v0->z + ((double)v1->z - (double)v0->z) * f;
        shade(d, (int)floorf(v0->x + dx * f), (int)floorf(v0->y + dy * f), a, z, a[5], a[6], a[7], a[8]);
    }
}

void gs_ref_draw(struct gs_ref *ref, const struct gs_batch *batch)
{
    const struct gs_pipe *p = batch->pipe;
    struct draw_ctx d;
    memset(&d, 0, sizeof(d));
    d.ref = ref;
    d.p = p;
    if (!is_colour_psm(p->fpsm)) {
        ref->stats.unsupported_targets++;
        return;
    }
    d.rt = colour_target(ref, p->fbp, p->fbw, p->fpsm);
    if (!d.rt)
        return;
    if (p->ztest != GS_CMP_ALWAYS || p->zwrite) {
        unsigned zpsm = p->zpsm;
        d.zmax = zpsm == GS_PSMZ32 ? 0xFFFFFFFFu : zpsm == GS_PSMZ24 ? 0xFFFFFFu : 0xFFFFu;
        d.zt = depth_target(ref, p->zbp, zpsm, p->fbw);
    }
    if (p->tme) {
        if (GS_FIELD(p->tex1, 2, 3))
            ref->stats.mip_ignored += batch->primitives;
        d.has_tex = texture_view(ref, p, &d.tex) == 0;
        if (!d.has_tex)
            return;
    }

    if (p->topology == GS_TOPOLOGY_LINES) {
        for (uint32_t i = 0; i + 1 < batch->count; i += 2)
            line(&d, &batch->vertices[i], &batch->vertices[i + 1]);
    } else {
        for (uint32_t i = 0; i + 2 < batch->count; i += 3)
            triangle(&d, &batch->vertices[i], &batch->vertices[i + 1], &batch->vertices[i + 2]);
    }
}

void gs_ref_transfer(struct gs_ref *ref, const struct gs_transfer *tr)
{
    ref->generation++;
    /* An upload over a target replaces what the target shows there. */
    for (int i = 0; i < GS_REF_TARGETS; i++) {
        struct gs_ref_target *rt = &ref->colour[i];
        if (rt->used && rt->base * 32 == tr->dbp && rt->fbw == tr->dbw && is_colour_psm(tr->dpsm)) {
            load_target_rect(ref, rt, tr->x, tr->y, tr->w, tr->h);
            ref->stats.rt_refreshes++;
        }
    }
}

void gs_ref_display(struct gs_ref *ref, const uint8_t *privregs)
{
    uint64_t pmode, dispfb, display, smode2;
    memcpy(&pmode, privregs + GS_PRIV_PMODE, 8);
    memcpy(&smode2, privregs + GS_PRIV_SMODE2, 8);
    /* Show read circuit 1 if it is on, else circuit 2. Merging both isn't modelled. */
    int circuit = (pmode & 1) ? 1 : (pmode & 2) ? 2 : 1;
    memcpy(&dispfb, privregs + (circuit == 1 ? GS_PRIV_DISPFB1 : GS_PRIV_DISPFB2), 8);
    memcpy(&display, privregs + (circuit == 1 ? GS_PRIV_DISPLAY1 : GS_PRIV_DISPLAY2), 8);

    uint32_t fbp = GS_FIELD(dispfb, 0, 9), fbw = GS_FIELD(dispfb, 9, 6);
    unsigned psm = GS_FIELD(dispfb, 15, 5);
    int dbx = (int)GS_FIELD(dispfb, 32, 11), dby = (int)GS_FIELD(dispfb, 43, 11);
    int w = (int)(GS_FIELD(display, 32, 12) + 1) / (int)(GS_FIELD(display, 23, 4) + 1);
    int h = (int)(GS_FIELD(display, 44, 11) + 1) / (int)(GS_FIELD(display, 27, 2) + 1);
    if ((smode2 & 1) && (smode2 & 2)) /* interlaced, field mode: each field is half the lines */
        h /= 2;
    w = clampi(w, 1, 2048);
    h = clampi(h, 1, 2048);

    uint8_t *frame = realloc(ref->frame, (size_t)w * h * 4);
    if (!frame)
        return;
    ref->frame = frame;
    ref->frame_width = w;
    ref->frame_height = h;
    ref->frames++;

    const struct gs_ref_target *rt = gs_ref_find_target(ref, fbp);
    if (rt && rt->fbw != fbw)
        rt = NULL;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            uint32_t c;
            int sx = dbx + x, sy = dby + y;
            if (rt) {
                c = 0;
                if (sx < rt->width && sy < rt->height)
                    memcpy(&c, rt->rgba + ((size_t)sy * rt->width + sx) * 4, 4);
            } else {
                c = gs_color_to_rgba(psm, gs_vram_read(ref->vram, fbp * 32, fbw, psm, sx, sy), RAW_TEXA);
            }
            c |= 0xFF000000u;
            memcpy(frame + ((size_t)y * w + x) * 4, &c, 4);
        }
}

static void sink_draw(void *user, const struct gs_batch *batch)
{
    gs_ref_draw(user, batch);
}

static void sink_transfer(void *user, const struct gs_transfer *transfer, const uint8_t *vram)
{
    (void)vram;
    gs_ref_transfer(user, transfer);
}

static void sink_vsync(void *user, const struct gs_display *display, const uint8_t *vram)
{
    (void)vram;
    gs_ref_display(user, display->privregs);
}

struct gs_sink gs_ref_sink(struct gs_ref *ref)
{
    struct gs_sink s = { ref, sink_draw, sink_transfer, sink_vsync };
    return s;
}
