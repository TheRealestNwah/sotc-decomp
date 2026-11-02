#include "gs_translate.h"

#include "gs_vram.h"
#include "gsdump.h"

#include <stdlib.h>
#include <string.h>

/* GIF tag FLG values. */
enum { FLG_PACKED = 0, FLG_REGLIST = 1, FLG_IMAGE = 2 };

static float bits_to_float(uint32_t bits)
{
    float f;
    memcpy(&f, &bits, sizeof(f));
    return f;
}

/* ---- blending ---- */

int gs_blend_map(uint64_t alpha, struct gs_blend *b)
{
    /* Operands: A, B, D select Cs (0), Cd (1) or 0 (2, and the reserved 3). */
    enum { CS = 0, CD = 1, Z = 2 };
    unsigned a = GS_FIELD(alpha, 0, 2), bb = GS_FIELD(alpha, 2, 2), c = GS_FIELD(alpha, 4, 2), d = GS_FIELD(alpha, 6, 2);
    if (a > Z)
        a = Z;
    if (bb > Z)
        bb = Z;
    if (d > Z)
        d = Z;

    memset(b, 0, sizeof(*b));
    b->enable = 1;
    b->c_source = c == 0 ? GS_BC_SRC_ALPHA : c == 1 ? GS_BC_DST_ALPHA : GS_BC_CONSTANT;
    b->fix = (uint8_t)GS_FIELD(alpha, 32, 8);
    b->op = GS_BO_ADD;
    b->exact = 1;

#define SET(s_, d_, op_) (b->src = (s_), b->dst = (d_), b->op = (op_))
    if (a == bb) {
        /* (A - A) * C + D = D */
        SET(d == CS ? GS_BF_ONE : GS_BF_ZERO, d == CD ? GS_BF_ONE : GS_BF_ZERO, GS_BO_ADD);
        return 1;
    }
    switch (a * 9 + bb * 3 + d) {
    case CS * 9 + CD * 3 + CD: /* Cs*C + Cd*(1-C) */
        SET(GS_BF_C, GS_BF_ONE_MINUS_C, GS_BO_ADD);
        break;
    case CS * 9 + CD * 3 + Z: /* (Cs - Cd)*C */
        SET(GS_BF_C, GS_BF_C, GS_BO_SUBTRACT);
        break;
    case CS * 9 + Z * 3 + CD: /* Cs*C + Cd */
        SET(GS_BF_C, GS_BF_ONE, GS_BO_ADD);
        break;
    case CS * 9 + Z * 3 + Z: /* Cs*C */
        SET(GS_BF_C, GS_BF_ZERO, GS_BO_ADD);
        break;
    case CD * 9 + CS * 3 + CS: /* Cs*(1-C) + Cd*C */
        SET(GS_BF_ONE_MINUS_C, GS_BF_C, GS_BO_ADD);
        break;
    case CD * 9 + CS * 3 + Z: /* (Cd - Cs)*C */
        SET(GS_BF_C, GS_BF_C, GS_BO_REVERSE_SUBTRACT);
        break;
    case CD * 9 + Z * 3 + CS: /* Cs + Cd*C */
        SET(GS_BF_ONE, GS_BF_C, GS_BO_ADD);
        break;
    case CD * 9 + Z * 3 + Z: /* Cd*C */
        SET(GS_BF_ZERO, GS_BF_C, GS_BO_ADD);
        break;
    case Z * 9 + CS * 3 + CS: /* Cs*(1-C) */
        SET(GS_BF_ONE_MINUS_C, GS_BF_ZERO, GS_BO_ADD);
        break;
    case Z * 9 + CS * 3 + CD: /* Cd - Cs*C */
        SET(GS_BF_C, GS_BF_ONE, GS_BO_REVERSE_SUBTRACT);
        break;
    case Z * 9 + CS * 3 + Z: /* -Cs*C, which clamps to 0 */
        SET(GS_BF_ZERO, GS_BF_ZERO, GS_BO_ADD);
        break;
    case Z * 9 + CD * 3 + CS: /* Cs - Cd*C */
        SET(GS_BF_ONE, GS_BF_C, GS_BO_SUBTRACT);
        break;
    case Z * 9 + CD * 3 + CD: /* Cd*(1-C) */
        SET(GS_BF_ZERO, GS_BF_ONE_MINUS_C, GS_BO_ADD);
        break;
    case Z * 9 + CD * 3 + Z: /* -Cd*C, which clamps to 0 */
        SET(GS_BF_ZERO, GS_BF_ZERO, GS_BO_ADD);
        break;
    /* A == D: one colour gets a (1 + C) weight. Drop the C term on it. */
    case CS * 9 + CD * 3 + CS: /* Cs*(1+C) - Cd*C ~ Cs - Cd*C */
        SET(GS_BF_ONE, GS_BF_C, GS_BO_SUBTRACT);
        b->exact = 0;
        break;
    case CS * 9 + Z * 3 + CS: /* Cs*(1+C) ~ Cs */
        SET(GS_BF_ONE, GS_BF_ZERO, GS_BO_ADD);
        b->exact = 0;
        break;
    case CD * 9 + CS * 3 + CD: /* Cd*(1+C) - Cs*C ~ Cd - Cs*C */
        SET(GS_BF_C, GS_BF_ONE, GS_BO_REVERSE_SUBTRACT);
        b->exact = 0;
        break;
    case CD * 9 + Z * 3 + CD: /* Cd*(1+C) ~ Cd */
        SET(GS_BF_ZERO, GS_BF_ONE, GS_BO_ADD);
        b->exact = 0;
        break;
    }
#undef SET
    return b->exact;
}

/* ---- setup ---- */

int gs_translator_init(struct gs_translator *t, const struct gs_sink *sink)
{
    memset(t, 0, sizeof(*t));
    t->vram = calloc(1, GS_VRAM_SIZE);
    t->batch = malloc(sizeof(*t->batch) * GS_BATCH_MAX_VERTICES);
    if (!t->vram || !t->batch) {
        gs_translator_free(t);
        return -1;
    }
    if (sink)
        t->sink = *sink;
    t->regs[GS_PRMODECONT] = 1;
    return 0;
}

void gs_translator_free(struct gs_translator *t)
{
    free(t->vram);
    free(t->batch);
    t->vram = NULL;
    t->batch = NULL;
}

void gs_translator_load(struct gs_translator *t, const struct gs_freeze *f, const uint8_t *privregs)
{
    uint64_t *r = t->regs;
    r[GS_PRIM] = f->prim;
    r[GS_PRMODE] = f->prim; /* the freeze keeps one PRIM; PRMODE takes the same attributes */
    r[GS_PRMODECONT] = f->prmodecont;
    r[GS_TEXCLUT] = f->texclut;
    r[GS_SCANMSK] = f->scanmsk;
    r[GS_TEXA] = f->texa;
    r[GS_FOGCOL] = f->fogcol;
    r[GS_DIMX] = f->dimx;
    r[GS_DTHE] = f->dthe;
    r[GS_COLCLAMP] = f->colclamp;
    r[GS_PABE] = f->pabe;
    r[GS_BITBLTBUF] = f->bitbltbuf;
    r[GS_TRXDIR] = f->trxdir;
    r[GS_TRXPOS] = f->trxpos;
    r[GS_TRXREG] = f->trxreg;
    for (int c = 0; c < 2; c++) {
        const struct gs_freeze_context *x = &f->ctx[c];
        r[GS_XYOFFSET_1 + c] = x->xyoffset;
        r[GS_TEX0_1 + c] = x->tex0;
        r[GS_TEX1_1 + c] = x->tex1;
        r[GS_CLAMP_1 + c] = x->clamp;
        r[GS_MIPTBP1_1 + c] = x->miptbp1;
        r[GS_MIPTBP2_1 + c] = x->miptbp2;
        r[GS_SCISSOR_1 + c] = x->scissor;
        r[GS_ALPHA_1 + c] = x->alpha;
        r[GS_TEST_1 + c] = x->test;
        r[GS_FBA_1 + c] = x->fba;
        r[GS_FRAME_1 + c] = x->frame;
        r[GS_ZBUF_1 + c] = x->zbuf;
    }
    r[GS_RGBAQ] = f->rgbaq;
    r[GS_ST] = f->st;
    r[GS_UV] = f->uv;
    r[GS_FOG] = f->fog;
    r[GS_XYZ2] = f->xyz;
    memcpy(&t->q_bits, &f->q, sizeof(t->q_bits));
    memcpy(t->vram, f->vram, GS_VRAM_SIZE);
    if (privregs)
        memcpy(t->privregs, privregs, GS_PRIV_SIZE);
    t->queued = 0;
}

/* ---- batching ---- */

void gs_translator_flush(struct gs_translator *t)
{
    if (!t->batch_count)
        return;
    struct gs_batch b = { &t->batch_pipe, t->batch, t->batch_count, t->batch_prims };
    t->stats.batches++;
    t->stats.batch_vertices += t->batch_count;
    if (t->sink.draw)
        t->sink.draw(t->sink.user, &b);
    t->batch_count = 0;
    t->batch_prims = 0;
}

/* PRIM with PRMODE's attributes when PRMODECONT.AC says so. */
static uint64_t effective_prim(const struct gs_translator *t)
{
    uint64_t prim = t->regs[GS_PRIM];
    if (!(t->regs[GS_PRMODECONT] & 1))
        prim = (prim & 7) | (t->regs[GS_PRMODE] & 0x7F8);
    return prim;
}

static unsigned compare_from_gs(unsigned atst)
{
    static const uint8_t map[8] = { GS_CMP_NEVER, GS_CMP_ALWAYS, GS_CMP_LESS, GS_CMP_LEQUAL, GS_CMP_EQUAL,
        GS_CMP_GEQUAL, GS_CMP_GREATER, GS_CMP_NOTEQUAL };
    return map[atst & 7];
}

static void build_pipe(struct gs_translator *t, uint64_t prim, int topology, struct gs_pipe *p)
{
    const uint64_t *r = t->regs;
    int ctx = GS_FIELD(prim, 9, 1);
    uint64_t frame = r[GS_FRAME_1 + ctx], zbuf = r[GS_ZBUF_1 + ctx], test = r[GS_TEST_1 + ctx];
    uint64_t scissor = r[GS_SCISSOR_1 + ctx];

    memset(p, 0, sizeof(*p));
    p->topology = (uint8_t)topology;
    p->fbp = (uint16_t)GS_FIELD(frame, 0, 9);
    p->fbw = (uint8_t)GS_FIELD(frame, 16, 6);
    p->fpsm = (uint8_t)GS_FIELD(frame, 24, 6);
    p->fbmsk = GS_FIELD(frame, 32, 32);

    p->zbp = (uint16_t)GS_FIELD(zbuf, 0, 9);
    p->zpsm = (uint8_t)(GS_FIELD(zbuf, 24, 4) | 0x30);
    if (GS_FIELD(test, 16, 1)) {
        static const uint8_t ztst[4] = { GS_CMP_NEVER, GS_CMP_ALWAYS, GS_CMP_GEQUAL, GS_CMP_GREATER };
        p->ztest = ztst[GS_FIELD(test, 17, 2)];
        p->zwrite = !GS_FIELD(zbuf, 32, 1);
    } else {
        /* ZTE = 0 is "not allowed" by the manual; hardware draws without depth. */
        p->ztest = GS_CMP_ALWAYS;
        p->zwrite = 0;
    }
    if (p->ztest == GS_CMP_ALWAYS && !p->zwrite)
        p->zbp = 0, p->zpsm = 0;

    if (GS_FIELD(test, 0, 1)) {
        p->atest = (uint8_t)compare_from_gs(GS_FIELD(test, 1, 3));
        p->aref = (uint8_t)GS_FIELD(test, 4, 8);
        p->afail = (uint8_t)GS_FIELD(test, 12, 2);
    } else {
        p->atest = GS_CMP_ALWAYS;
    }
    p->date = (uint8_t)GS_FIELD(test, 14, 1);
    p->datm = p->date ? (uint8_t)GS_FIELD(test, 15, 1) : 0;

    if (GS_FIELD(prim, 6, 1) || GS_FIELD(prim, 7, 1)) {
        if (!gs_blend_map(r[GS_ALPHA_1 + ctx], &p->blend))
            t->stats.blend_approx++;
        p->pabe = (uint8_t)(r[GS_PABE] & 1);
    }

    if (GS_FIELD(prim, 4, 1)) {
        p->tme = 1;
        p->tex0 = r[GS_TEX0_1 + ctx];
        p->tex1 = r[GS_TEX1_1 + ctx];
        p->clamp = r[GS_CLAMP_1 + ctx];
        p->texa = r[GS_TEXA];
        p->texclut = r[GS_TEXCLUT];
        p->tfx = (uint8_t)GS_FIELD(p->tex0, 35, 2);
        p->tcc = (uint8_t)GS_FIELD(p->tex0, 34, 1);
        /* Fields that don't change how the texture samples. */
        p->tex0 &= ~(7ull << 61); /* CLD */
        if (gs_psm_bpp(GS_FIELD(p->tex0, 20, 6)) > 8) {
            p->tex0 &= ~(0x3FFFull << 37 | 0xFull << 51 | 1ull << 55 | 0x1Full << 56); /* CBP, CPSM, CSM, CSA */
            p->texclut = 0;
        }
        if (GS_FIELD(p->tex0, 20, 6) == GS_PSMCT32)
            p->texa = 0;
    }
    if (GS_FIELD(prim, 5, 1)) {
        p->fge = 1;
        p->fogcol = GS_FIELD(r[GS_FOGCOL], 0, 24);
    }

    p->scissor[0] = (uint16_t)GS_FIELD(scissor, 0, 11);
    p->scissor[1] = (uint16_t)GS_FIELD(scissor, 16, 11);
    p->scissor[2] = (uint16_t)GS_FIELD(scissor, 32, 11);
    p->scissor[3] = (uint16_t)GS_FIELD(scissor, 48, 11);
    p->colclamp = (uint8_t)(r[GS_COLCLAMP] & 1);
    p->fba = (uint8_t)(r[GS_FBA_1 + ctx] & 1);
    p->dthe = (uint8_t)(r[GS_DTHE] & 1);
}

static void emit(struct gs_translator *t, uint64_t prim, int topology, const struct gs_vertex *v, uint32_t n)
{
    struct gs_pipe p;
    build_pipe(t, prim, topology, &p);
    if (t->batch_count && (memcmp(&p, &t->batch_pipe, sizeof(p)) != 0 || t->batch_count + n > GS_BATCH_MAX_VERTICES))
        gs_translator_flush(t);
    if (!t->batch_count)
        memcpy(&t->batch_pipe, &p, sizeof(p));
    memcpy(t->batch + t->batch_count, v, sizeof(*v) * n);
    t->batch_count += n;
    t->batch_prims++;
    t->stats.primitives[GS_FIELD(prim, 0, 3)]++;

    uint32_t mask = p.fbmsk;
    for (int i = 0; i < 4; i++, mask >>= 8)
        if ((mask & 0xFF) != 0 && (mask & 0xFF) != 0xFF) {
            t->stats.fbmsk_partial++;
            break;
        }
    if (!p.colclamp && p.blend.enable)
        t->stats.colclamp_off++;
}

/* ---- primitive assembly ---- */

static struct gs_vertex make_vertex(struct gs_translator *t, uint64_t prim, uint64_t xyz, int with_fog)
{
    const uint64_t *r = t->regs;
    int ctx = GS_FIELD(prim, 9, 1);
    uint64_t ofs = r[GS_XYOFFSET_1 + ctx];
    struct gs_vertex v;
    memset(&v, 0, sizeof(v));

    v.x = (float)((int)GS_FIELD(xyz, 0, 16) - (int)GS_FIELD(ofs, 0, 16)) / 16.0f;
    v.y = (float)((int)GS_FIELD(xyz, 16, 16) - (int)GS_FIELD(ofs, 32, 16)) / 16.0f;
    if (with_fog) {
        v.z = GS_FIELD(xyz, 32, 24);
        v.fog = (uint8_t)GS_FIELD(xyz, 56, 8);
    } else {
        v.z = GS_FIELD(xyz, 32, 32);
        v.fog = (uint8_t)GS_FIELD(r[GS_FOG], 56, 8);
    }

    uint64_t rgbaq = r[GS_RGBAQ];
    v.r = (uint8_t)GS_FIELD(rgbaq, 0, 8);
    v.g = (uint8_t)GS_FIELD(rgbaq, 8, 8);
    v.b = (uint8_t)GS_FIELD(rgbaq, 16, 8);
    v.a = (uint8_t)GS_FIELD(rgbaq, 24, 8);

    int tw, th;
    gs_tex_size(r[GS_TEX0_1 + ctx], &tw, &th);
    if (GS_FIELD(prim, 8, 1)) {
        /* FST: UV in 12.4 texels. */
        v.s = (float)GS_FIELD(r[GS_UV], 0, 14) / 16.0f / (float)tw;
        v.t = (float)GS_FIELD(r[GS_UV], 16, 14) / 16.0f / (float)th;
        v.q = 1.0f;
    } else {
        v.s = bits_to_float(GS_FIELD(r[GS_ST], 0, 32));
        v.t = bits_to_float(GS_FIELD(r[GS_ST], 32, 32));
        v.q = bits_to_float(GS_FIELD(rgbaq, 32, 32));
    }
    return v;
}

static void flat_colour(struct gs_vertex *v, int n)
{
    for (int i = 0; i < n - 1; i++) {
        v[i].r = v[n - 1].r;
        v[i].g = v[n - 1].g;
        v[i].b = v[n - 1].b;
        v[i].a = v[n - 1].a;
    }
}

static void emit_triangle(struct gs_translator *t, uint64_t prim, const struct gs_vertex *a, const struct gs_vertex *b,
    const struct gs_vertex *c)
{
    struct gs_vertex v[3] = { *a, *b, *c };
    if (!GS_FIELD(prim, 3, 1))
        flat_colour(v, 3);
    emit(t, prim, GS_TOPOLOGY_TRIANGLES, v, 3);
}

static void emit_line(struct gs_translator *t, uint64_t prim, const struct gs_vertex *a, const struct gs_vertex *b)
{
    struct gs_vertex v[2] = { *a, *b };
    if (!GS_FIELD(prim, 3, 1))
        flat_colour(v, 2);
    emit(t, prim, GS_TOPOLOGY_LINES, v, 2);
}

/* A sprite is an axis-aligned rectangle with v1's colour, depth and fog. */
static void emit_sprite(struct gs_translator *t, uint64_t prim, const struct gs_vertex *a, const struct gs_vertex *b)
{
    struct gs_vertex c[4];
    float s0 = a->s / (a->q ? a->q : 1.0f), t0 = a->t / (a->q ? a->q : 1.0f);
    float s1 = b->s / (b->q ? b->q : 1.0f), t1 = b->t / (b->q ? b->q : 1.0f);
    for (int i = 0; i < 4; i++) {
        c[i] = *b;
        c[i].x = (i & 1) ? b->x : a->x;
        c[i].y = (i & 2) ? b->y : a->y;
        c[i].s = (i & 1) ? s1 : s0;
        c[i].t = (i & 2) ? t1 : t0;
        c[i].q = 1.0f;
    }
    struct gs_vertex v[6] = { c[0], c[1], c[2], c[1], c[3], c[2] };
    emit(t, prim, GS_TOPOLOGY_TRIANGLES, v, 6);
}

static void vertex_kick(struct gs_translator *t, uint64_t xyz, int with_fog, int draw)
{
    uint64_t prim = effective_prim(t);
    struct gs_vertex v = make_vertex(t, prim, xyz, with_fog);
    struct gs_vertex *q = t->queue;
    unsigned type = GS_FIELD(prim, 0, 3);

    t->stats.vertices++;
    if (!draw)
        t->stats.vertices_no_kick++;
    q[t->queued++] = v;

    switch (type) {
    case GS_PRIM_POINT: {
        if (draw) {
            /* A point covers one pixel: draw it as a 1x1 sprite. */
            struct gs_vertex b = v;
            b.x += 1.0f;
            b.y += 1.0f;
            emit_sprite(t, prim, &v, &b);
        }
        t->queued = 0;
        break;
    }
    case GS_PRIM_LINE:
        if (t->queued == 2) {
            if (draw)
                emit_line(t, prim, &q[0], &q[1]);
            t->queued = 0;
        }
        break;
    case GS_PRIM_LINESTRIP:
        if (t->queued == 2) {
            if (draw)
                emit_line(t, prim, &q[0], &q[1]);
            q[0] = q[1];
            t->queued = 1;
        }
        break;
    case GS_PRIM_TRIANGLE:
        if (t->queued == 3) {
            if (draw)
                emit_triangle(t, prim, &q[0], &q[1], &q[2]);
            t->queued = 0;
        }
        break;
    case GS_PRIM_TRISTRIP:
        if (t->queued == 3) {
            if (draw)
                emit_triangle(t, prim, &q[0], &q[1], &q[2]);
            q[0] = q[1];
            q[1] = q[2];
            t->queued = 2;
        }
        break;
    case GS_PRIM_TRIFAN:
        if (t->queued == 3) {
            if (draw)
                emit_triangle(t, prim, &q[0], &q[1], &q[2]);
            q[1] = q[2];
            t->queued = 2;
        }
        break;
    case GS_PRIM_SPRITE:
        if (t->queued == 2) {
            if (draw)
                emit_sprite(t, prim, &q[0], &q[1]);
            t->queued = 0;
        }
        break;
    default:
        t->queued = 0;
        break;
    }
}

/* ---- image transfers ---- */

static void transfer_done(struct gs_translator *t, int local, uint32_t dbp, uint32_t dbw, uint32_t dpsm, int x, int y,
    int w, int h)
{
    struct gs_transfer tr = { local, dbp, dbw, dpsm, x, y, w, h };
    if (t->sink.transfer)
        t->sink.transfer(t->sink.user, &tr, t->vram);
}

static void image_pixel(struct gs_translator *t, uint32_t value)
{
    if (!t->image.active)
        return;
    gs_vram_write(t->vram, t->image.dbp, t->image.dbw, t->image.dpsm, t->image.x0 + t->image.x,
        t->image.y0 + t->image.y, value);
    if (++t->image.x >= t->image.w) {
        t->image.x = 0;
        if (++t->image.y >= t->image.h) {
            t->image.active = 0;
            transfer_done(t, 0, t->image.dbp, t->image.dbw, t->image.dpsm, t->image.x0, t->image.y0, t->image.w,
                t->image.h);
        }
    }
}

static void image_bytes(struct gs_translator *t, const uint8_t *data, size_t n)
{
    t->stats.transfer_bytes += n;
    if (!t->image.active)
        return;
    unsigned bpp = gs_psm_bpp(t->image.dpsm);
    for (size_t i = 0; i < n && t->image.active; i++) {
        if (bpp == 4) {
            image_pixel(t, data[i] & 0xF);
            image_pixel(t, data[i] >> 4);
            continue;
        }
        t->image.acc |= (uint32_t)data[i] << (8 * t->image.acc_bytes);
        if (++t->image.acc_bytes * 8 == bpp) {
            image_pixel(t, t->image.acc);
            t->image.acc = 0;
            t->image.acc_bytes = 0;
        }
    }
}

static void start_transfer(struct gs_translator *t, unsigned dir)
{
    const uint64_t *r = t->regs;
    uint64_t blt = r[GS_BITBLTBUF], pos = r[GS_TRXPOS], reg = r[GS_TRXREG];
    int w = (int)GS_FIELD(reg, 0, 12), h = (int)GS_FIELD(reg, 32, 12);

    /* Draws queued before the transfer must see the old memory. */
    gs_translator_flush(t);
    t->image.active = 0;

    switch (dir) {
    case 0: { /* host -> local */
        uint32_t psm = GS_FIELD(blt, 56, 6);
        t->stats.transfers_host++;
        if (!gs_psm_known(psm)) {
            t->stats.unknown_psm_transfers++;
            return;
        }
        t->image.dbp = GS_FIELD(blt, 32, 14);
        t->image.dbw = GS_FIELD(blt, 48, 6);
        t->image.dpsm = psm;
        t->image.x0 = (int)GS_FIELD(pos, 32, 11);
        t->image.y0 = (int)GS_FIELD(pos, 48, 11);
        t->image.w = w;
        t->image.h = h;
        t->image.x = t->image.y = 0;
        t->image.acc = t->image.acc_bytes = 0;
        t->image.active = w > 0 && h > 0;
        break;
    }
    case 1: /* local -> host: the game reading memory back; nothing to draw */
        t->stats.transfers_readback++;
        break;
    case 2: { /* local -> local */
        uint32_t sbp = GS_FIELD(blt, 0, 14), sbw = GS_FIELD(blt, 16, 6), spsm = GS_FIELD(blt, 24, 6);
        uint32_t dbp = GS_FIELD(blt, 32, 14), dbw = GS_FIELD(blt, 48, 6), dpsm = GS_FIELD(blt, 56, 6);
        int sx = (int)GS_FIELD(pos, 0, 11), sy = (int)GS_FIELD(pos, 16, 11);
        int dx = (int)GS_FIELD(pos, 32, 11), dy = (int)GS_FIELD(pos, 48, 11);
        t->stats.transfers_local++;
        if (!gs_psm_known(spsm) || !gs_psm_known(dpsm) || w <= 0 || h <= 0) {
            t->stats.unknown_psm_transfers++;
            return;
        }
        /* Copy through a buffer so overlapping rectangles behave like a whole-rectangle move. */
        uint32_t *tmp = malloc(sizeof(*tmp) * (size_t)w * (size_t)h);
        if (!tmp)
            return;
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                tmp[(size_t)y * w + x] = gs_vram_read(t->vram, sbp, sbw, spsm, sx + x, sy + y);
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                gs_vram_write(t->vram, dbp, dbw, dpsm, dx + x, dy + y, tmp[(size_t)y * w + x]);
        free(tmp);
        transfer_done(t, 1, dbp, dbw, dpsm, dx, dy, w, h);
        break;
    }
    default:
        break;
    }
}

/* ---- registers ---- */

void gs_translator_write(struct gs_translator *t, uint32_t reg, uint64_t value)
{
    switch (reg) {
    case GS_PRIM:
        t->regs[GS_PRIM] = value & 0x7FF;
        t->queued = 0;
        return;
    case GS_XYZF2:
    case GS_XYZ2:
    case GS_XYZF3:
    case GS_XYZ3:
        t->regs[reg] = value;
        vertex_kick(t, value, reg == GS_XYZF2 || reg == GS_XYZF3, reg == GS_XYZF2 || reg == GS_XYZ2);
        return;
    case GS_TEX2_1:
    case GS_TEX2_2: {
        /* TEX2 replaces TEX0's PSM and CLUT fields only. */
        const uint64_t mask = 0x3Full << 20 | ~0ull << 37;
        uint64_t *tex0 = &t->regs[GS_TEX0_1 + (reg - GS_TEX2_1)];
        *tex0 = (*tex0 & ~mask) | (value & mask);
        return;
    }
    case GS_TRXDIR:
        t->regs[reg] = value;
        start_transfer(t, GS_FIELD(value, 0, 2));
        return;
    case GS_HWREG: {
        uint8_t bytes[8];
        for (int i = 0; i < 8; i++)
            bytes[i] = (uint8_t)(value >> (8 * i));
        image_bytes(t, bytes, 8);
        return;
    }
    default:
        if (reg < GS_REG_COUNT)
            t->regs[reg] = value;
        else
            t->stats.unknown_regs++;
        return;
    }
}

static uint64_t rd64(const uint8_t *p)
{
    uint64_t v = 0;
    for (int i = 7; i >= 0; i--)
        v = v << 8 | p[i];
    return v;
}

/* One PACKED-mode register write; descriptors 0x0-0xD name their own register. */
static void packed_write(struct gs_translator *t, unsigned desc, uint64_t lo, uint64_t hi)
{
    switch (desc) {
    case 0x0: /* PRIM */
        gs_translator_write(t, GS_PRIM, lo & 0x7FF);
        break;
    case 0x1: /* RGBAQ: one byte per 32-bit lane, Q from the last ST */
        t->regs[GS_RGBAQ] = (lo & 0xFF) | ((lo >> 32) & 0xFF) << 8 | (hi & 0xFF) << 16 | ((hi >> 32) & 0xFF) << 24 |
            (uint64_t)t->q_bits << 32;
        break;
    case 0x2: /* ST, with Q in the third lane */
        t->regs[GS_ST] = lo;
        t->q_bits = (uint32_t)hi;
        break;
    case 0x3: /* UV */
        t->regs[GS_UV] = (lo & 0x3FFF) | ((lo >> 32) & 0x3FFF) << 16;
        break;
    case 0x4: /* XYZF2; ADC turns it into XYZF3 */
    case 0xC: {
        uint64_t v = (lo & 0xFFFF) | ((lo >> 32) & 0xFFFF) << 16 | ((hi >> 4) & 0xFFFFFF) << 32 | ((hi >> 36) & 0xFF)
            << 56;
        gs_translator_write(t, (desc == 0xC || (hi >> 47 & 1)) ? GS_XYZF3 : GS_XYZF2, v);
        break;
    }
    case 0x5: /* XYZ2; ADC turns it into XYZ3 */
    case 0xD: {
        uint64_t v = (lo & 0xFFFF) | ((lo >> 32) & 0xFFFF) << 16 | (hi & 0xFFFFFFFF) << 32;
        gs_translator_write(t, (desc == 0xD || (hi >> 47 & 1)) ? GS_XYZ3 : GS_XYZ2, v);
        break;
    }
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
        gs_translator_write(t, desc, lo);
        break;
    case 0xA: /* FOG */
        t->regs[GS_FOG] = ((hi >> 36) & 0xFF) << 56;
        break;
    case 0xE: /* A+D */
        gs_translator_write(t, (uint32_t)(hi & 0xFF), lo);
        break;
    default: /* 0xB reserved, 0xF NOP */
        break;
    }
}

static void gif_qword(struct gs_translator *t, struct gs_gif_path *p, const uint8_t *q)
{
    uint64_t lo = rd64(q), hi = rd64(q + 8);

    if (p->nloop == 0) {
        /* A GIF tag. */
        p->nloop = GS_FIELD(lo, 0, 15);
        p->flg = GS_FIELD(lo, 58, 2);
        p->nreg = GS_FIELD(lo, 60, 4);
        if (p->nreg == 0)
            p->nreg = 16;
        p->regs = hi;
        p->reg = 0;
        t->stats.gif_tags++;
        t->stats.gif_tags_by_flg[p->flg]++;
        if (p->flg == FLG_PACKED && GS_FIELD(lo, 46, 1))
            gs_translator_write(t, GS_PRIM, GS_FIELD(lo, 47, 11));
        if (p->flg == 3)
            p->flg = FLG_IMAGE; /* FLG 3 behaves as IMAGE */
        return;
    }

    switch (p->flg) {
    case FLG_PACKED:
        packed_write(t, (unsigned)(p->regs >> (4 * p->reg)) & 0xF, lo, hi);
        if (++p->reg == p->nreg) {
            p->reg = 0;
            p->nloop--;
        }
        break;
    case FLG_REGLIST: {
        uint64_t half[2] = { lo, hi };
        for (int i = 0; i < 2 && p->nloop; i++) {
            unsigned desc = (unsigned)(p->regs >> (4 * p->reg)) & 0xF;
            if (desc < 0xE)
                gs_translator_write(t, desc, half[i]);
            if (++p->reg == p->nreg) {
                p->reg = 0;
                p->nloop--;
            }
        }
        /* An odd register count leaves the last qword's high half as padding. */
        break;
    }
    default: /* IMAGE */
        image_bytes(t, q, 16);
        p->nloop--;
        break;
    }
}

void gs_translator_gif(struct gs_translator *t, int path, const uint8_t *data, size_t size)
{
    if (path < 1 || path > 3)
        return;
    struct gs_gif_path *p = &t->path[path];
    while (size) {
        if (p->partial_size || size < 16) {
            size_t n = 16 - p->partial_size;
            if (n > size)
                n = size;
            memcpy(p->partial + p->partial_size, data, n);
            p->partial_size += (uint32_t)n;
            data += n;
            size -= n;
            if (p->partial_size == 16) {
                p->partial_size = 0;
                t->stats.qwords[path]++;
                gif_qword(t, p, p->partial);
            }
            continue;
        }
        t->stats.qwords[path]++;
        gif_qword(t, p, data);
        data += 16;
        size -= 16;
    }
}

void gs_translator_vsync(struct gs_translator *t, int field)
{
    gs_translator_flush(t);
    t->stats.vsyncs++;
    struct gs_display d = { t->privregs, field };
    if (t->sink.vsync)
        t->sink.vsync(t->sink.user, &d, t->vram);
}

int gs_translator_packet(struct gs_translator *t, const struct gs_dump_packet *pk)
{
    switch (pk->type) {
    case GS_DUMP_TRANSFER: {
        static const int paths[4] = { 1, 2, 3, 1 }; /* PATH1 (old), PATH2, PATH3, PATH1 */
        if (pk->path >= 0 && pk->path < 4)
            gs_translator_gif(t, paths[pk->path], pk->data, pk->size);
        return 0;
    }
    case GS_DUMP_VSYNC:
        gs_translator_vsync(t, pk->field);
        return 1;
    case GS_DUMP_REGISTERS:
        memcpy(t->privregs, pk->data, GS_PRIV_SIZE);
        return 0;
    default:
        return 0;
    }
}
