/* Render translator front end, on GIF packets built by hand (synthetic data only). */
#include "check.h"
#include "gif.h"
#include "gs_regs.h"
#include "gs_translate.h"
#include "gs_vram.h"
#include "gsdump.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { FLG_PACKED = 0, FLG_REGLIST = 1, FLG_IMAGE = 2 };

#define MAX_BATCHES 16
#define MAX_VERTICES 64

/* A sink that records what it is given. */
struct recorder {
    int batches;
    struct gs_pipe pipe[MAX_BATCHES];
    struct gs_vertex v[MAX_BATCHES][MAX_VERTICES];
    uint32_t count[MAX_BATCHES], prims[MAX_BATCHES];
    int transfers;
    struct gs_transfer transfer;
    int vsyncs;
};

static void rec_draw(void *user, const struct gs_batch *b)
{
    struct recorder *r = user;
    if (r->batches < MAX_BATCHES) {
        r->pipe[r->batches] = *b->pipe;
        memcpy(r->v[r->batches], b->vertices,
            sizeof(*b->vertices) * (b->count < MAX_VERTICES ? b->count : MAX_VERTICES));
        r->count[r->batches] = b->count;
        r->prims[r->batches] = b->primitives;
    }
    r->batches++;
}

static void rec_transfer(void *user, const struct gs_transfer *tr, const uint8_t *vram)
{
    struct recorder *r = user;
    (void)vram;
    r->transfer = *tr;
    r->transfers++;
}

static void rec_vsync(void *user, const struct gs_display *d, const uint8_t *vram)
{
    struct recorder *r = user;
    (void)d;
    (void)vram;
    r->vsyncs++;
}

static struct recorder rec;
static struct gs_translator t;
static int t_live;
static struct gif g;

static void start(void)
{
    struct gs_sink sink = { &rec, rec_draw, rec_transfer, rec_vsync };
    memset(&rec, 0, sizeof(rec));
    if (t_live)
        gs_translator_free(&t);
    if (gs_translator_init(&t, &sink) != 0)
        exit(1);
    t_live = 1;
    g.size = 0;
}

static void send_gif(void)
{
    gs_translator_gif(&t, 3, g.data, g.size);
    g.size = 0;
}

static void ad_tag(unsigned n)
{
    gif_tag(&g, n, 0, 0, 0, FLG_PACKED, 1, 0xE);
}

/* A PACKED sprite: PRE sets PRIM, then RGBAQ + XYZ2 twice (pixel coordinates). */
static void sprite(uint64_t prim, unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned r)
{
    gif_tag(&g, 2, 1, 1, (unsigned)prim, FLG_PACKED, 2, 0x51);
    gif_rgbaq(&g, r, 0, 0, 0x80);
    gif_xyz2(&g, x0 * 16, y0 * 16, 0, 0);
    gif_rgbaq(&g, r + 1, 0, 0, 0x80);
    gif_xyz2(&g, x1 * 16, y1 * 16, 0, 0);
}

static int near(float a, float b)
{
    return fabsf(a - b) < 1e-4f;
}

static void test_sprite_and_offset(void)
{
    start();
    ad_tag(2);
    gif_ad(&g, GS_FRAME_1, gs_frame(5, 2, GS_PSMCT32, 0));
    gif_ad(&g, GS_XYOFFSET_1, gs_xyoffset(100 * 16, 200 * 16));
    sprite(gs_prim(GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0), 110, 220, 130, 240, 7);
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 1);
    CHECK_EQ(rec.count[0], 6u);
    CHECK_EQ(rec.prims[0], 1u);
    /* Corners in order c0, c1, c2, c1, c3, c2. */
    CHECK(near(rec.v[0][0].x, 10) && near(rec.v[0][0].y, 20));
    CHECK(near(rec.v[0][1].x, 30) && near(rec.v[0][1].y, 20));
    CHECK(near(rec.v[0][2].x, 10) && near(rec.v[0][2].y, 40));
    CHECK(near(rec.v[0][4].x, 30) && near(rec.v[0][4].y, 40));
    /* A sprite takes the second vertex's colour. */
    CHECK_EQ(rec.v[0][0].r, 8);
    CHECK_EQ(rec.v[0][0].a, 0x80);
    CHECK_EQ(rec.pipe[0].fbp, 5u);
    CHECK_EQ(rec.pipe[0].fbw, 2u);
    CHECK_EQ(rec.pipe[0].topology, GS_TOPOLOGY_TRIANGLES);
    CHECK_EQ(rec.pipe[0].ztest, GS_CMP_ALWAYS);
    CHECK_EQ(rec.pipe[0].zwrite, 0);
    CHECK_EQ(rec.pipe[0].blend.enable, 0);
    CHECK_EQ(t.stats.primitives[GS_PRIM_SPRITE], 1u);
}

static void test_batching(void)
{
    uint64_t prim = gs_prim(GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0);
    start();
    sprite(prim, 0, 0, 1, 1, 1);
    sprite(prim, 2, 2, 3, 3, 1);
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 1);
    CHECK_EQ(rec.count[0], 12u);
    CHECK_EQ(rec.prims[0], 2u);

    start();
    sprite(prim, 0, 0, 1, 1, 1);
    ad_tag(1);
    gif_ad(&g, GS_FRAME_1, gs_frame(8, 1, GS_PSMCT32, 0));
    sprite(prim, 2, 2, 3, 3, 1);
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 2);
    CHECK_EQ(rec.pipe[1].fbp, 8u);
    CHECK_EQ(t.stats.batches, 2u);
}

/* Four vertices at x = 0..3 through a strip or fan; returns how many were emitted, with their x in xs. */
static int run_four(unsigned type, int adc_third, float *xs)
{
    start();
    gif_tag(&g, 4, 1, 1, (unsigned)gs_prim(type, 1, 0, 0, 0, 0, 0), FLG_PACKED, 1, 0x5);
    for (unsigned i = 0; i < 4; i++)
        gif_xyz2(&g, i * 16, (i & 1) * 16, 0, adc_third && i == 2);
    send_gif();
    gs_translator_flush(&t);
    int n = rec.batches ? (int)rec.count[0] : 0;
    for (int i = 0; i < n && i < 12; i++)
        xs[i] = rec.v[0][i].x;
    return n;
}

static void test_strips(void)
{
    float xs[12];
    CHECK_EQ(run_four(GS_PRIM_TRISTRIP, 0, xs), 6);
    CHECK(xs[0] == 0 && xs[1] == 1 && xs[2] == 2 && xs[3] == 1 && xs[4] == 2 && xs[5] == 3);
    CHECK_EQ(run_four(GS_PRIM_TRIFAN, 0, xs), 6);
    CHECK(xs[0] == 0 && xs[1] == 1 && xs[2] == 2 && xs[3] == 0 && xs[4] == 2 && xs[5] == 3);
    /* ADC on the third vertex queues it without drawing the first triangle. */
    CHECK_EQ(run_four(GS_PRIM_TRISTRIP, 1, xs), 3);
    CHECK(xs[0] == 1 && xs[1] == 2 && xs[2] == 3);
    CHECK_EQ(t.stats.vertices_no_kick, 1u);
    CHECK_EQ(run_four(GS_PRIM_LINESTRIP, 0, xs), 6);
    CHECK_EQ(rec.pipe[0].topology, GS_TOPOLOGY_LINES);
    CHECK(xs[0] == 0 && xs[1] == 1 && xs[2] == 1 && xs[3] == 2 && xs[4] == 2 && xs[5] == 3);
}

static void test_flat_shading(void)
{
    start();
    gif_tag(&g, 3, 1, 1, (unsigned)gs_prim(GS_PRIM_TRIANGLE, 0, 0, 0, 0, 0, 0), FLG_PACKED, 2, 0x51);
    for (unsigned i = 0; i < 3; i++) {
        gif_rgbaq(&g, 10 * (i + 1), 0, 0, 0x80);
        gif_xyz2(&g, i * 16, i * 16, 0, 0);
    }
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.count[0], 3u);
    CHECK(rec.v[0][0].r == 30 && rec.v[0][1].r == 30 && rec.v[0][2].r == 30);
}

static void test_reglist(void)
{
    start();
    /* PRIM, RGBAQ, XYZ2: three registers, so the second qword's high half is padding. */
    gif_tag(&g, 1, 0, 0, 0, FLG_REGLIST, 3, 0x510);
    gif_qword(&g, gs_prim(GS_PRIM_POINT, 0, 0, 0, 0, 0, 0), 0x80332211u);
    gif_qword(&g, (uint64_t)(5 * 16) | (uint64_t)(6 * 16) << 16, 0xDEADBEEFDEADBEEFull);
    ad_tag(1);
    gif_ad(&g, GS_FRAME_1, gs_frame(3, 1, GS_PSMCT32, 0));
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 1);
    CHECK_EQ(rec.count[0], 6u); /* a point is a 1x1 sprite */
    CHECK(near(rec.v[0][0].x, 5) && near(rec.v[0][0].y, 6) && near(rec.v[0][4].x, 6) && near(rec.v[0][4].y, 7));
    CHECK(rec.v[0][0].r == 0x11 && rec.v[0][0].g == 0x22 && rec.v[0][0].b == 0x33 && rec.v[0][0].a == 0x80);
    CHECK(t.regs[GS_FRAME_1] == gs_frame(3, 1, GS_PSMCT32, 0));
    CHECK_EQ(t.stats.gif_tags, 2u);
}

static void image_setup(unsigned dbp, unsigned psm, unsigned dx, unsigned dy, unsigned w, unsigned h)
{
    ad_tag(4);
    gif_ad(&g, GS_BITBLTBUF, gs_bitbltbuf(dbp, 1, psm));
    gif_ad(&g, GS_TRXPOS, gs_trxpos(0, 0, dx, dy));
    gif_ad(&g, GS_TRXREG, gs_trxreg(w, h));
    gif_ad(&g, GS_TRXDIR, 0);
}

static void test_images(void)
{
    /* CT32, 4x2 at (2, 3). */
    start();
    image_setup(0x100, GS_PSMCT32, 2, 3, 4, 2);
    gif_tag(&g, 2, 1, 0, 0, FLG_IMAGE, 0, 0);
    for (uint32_t i = 0; i < 8; i += 2)
        gif_u64(&g, (uint64_t)(0x80000000u | i) | (uint64_t)(0x80000000u | (i + 1)) << 32);
    send_gif();
    int ok = 1;
    for (unsigned y = 0; y < 2; y++)
        for (unsigned x = 0; x < 4; x++)
            if (gs_vram_read(t.vram, 0x100, 1, GS_PSMCT32, 2 + x, 3 + y) != (0x80000000u | (y * 4 + x)))
                ok = 0;
    CHECK(ok);
    CHECK_EQ(rec.transfers, 1);
    CHECK(rec.transfer.local == 0 && rec.transfer.dbp == 0x100 && rec.transfer.x == 2 && rec.transfer.y == 3
        && rec.transfer.w == 4 && rec.transfer.h == 2);
    CHECK_EQ(t.stats.transfers_host, 1u);

    /* Local -> local: copy that rectangle to (0, 0) at 0x200. */
    ad_tag(4);
    gif_ad(&g, GS_BITBLTBUF, 0x100 | 1ull << 16 | (uint64_t)GS_PSMCT32 << 24 | gs_bitbltbuf(0x200, 1, GS_PSMCT32));
    gif_ad(&g, GS_TRXPOS, gs_trxpos(2, 3, 0, 0));
    gif_ad(&g, GS_TRXREG, gs_trxreg(4, 2));
    gif_ad(&g, GS_TRXDIR, 2);
    send_gif();
    CHECK(gs_vram_read(t.vram, 0x200, 1, GS_PSMCT32, 3, 1) == 0x80000007u);
    CHECK(gs_vram_read(t.vram, 0x200, 1, GS_PSMCT32, 0, 0) == 0x80000000u);
    CHECK_EQ(rec.transfers, 2);
    CHECK(rec.transfer.local == 1 && rec.transfer.dbp == 0x200);
    CHECK_EQ(t.stats.transfers_local, 1u);

    /* CT24, 16x1: 48 bytes, three bytes per pixel. */
    start();
    image_setup(0x100, GS_PSMCT24, 0, 0, 16, 1);
    gif_tag(&g, 3, 1, 0, 0, FLG_IMAGE, 0, 0);
    for (unsigned i = 0; i < 48; i++)
        g.data[g.size++] = (uint8_t)i;
    send_gif();
    CHECK(gs_vram_read(t.vram, 0x100, 1, GS_PSMCT24, 0, 0) == 0x020100u);
    CHECK(gs_vram_read(t.vram, 0x100, 1, GS_PSMCT24, 15, 0) == 0x2F2E2Du);

    /* T4, 32x1: the low nibble is the first pixel. */
    start();
    image_setup(0x100, GS_PSMT4, 0, 0, 32, 1);
    gif_tag(&g, 1, 1, 0, 0, FLG_IMAGE, 0, 0);
    for (unsigned i = 0; i < 16; i++)
        g.data[g.size++] = (uint8_t)(((2 * i + 1) & 15) << 4 | ((2 * i) & 15));
    send_gif();
    ok = 1;
    for (unsigned x = 0; x < 32; x++)
        if (gs_vram_read(t.vram, 0x100, 1, GS_PSMT4, x, 0) != (x & 15))
            ok = 0;
    CHECK(ok);
    CHECK_EQ(rec.transfer.w, 32u);
}

static void test_tex2(void)
{
    start();
    gs_translator_write(&t, GS_TEX0_1, gs_tex0(0x100, 1, GS_PSMCT32, 4, 4, 1, 0, 0, 0));
    gs_translator_write(&t, GS_TEX2_1, (uint64_t)GS_PSMT8 << 20 | 0x300ull << 37 | 0x3FFFull);
    uint64_t tex0 = t.regs[GS_TEX0_1];
    CHECK_EQ(GS_FIELD(tex0, 0, 14), 0x100u); /* TBP kept */
    CHECK_EQ(GS_FIELD(tex0, 20, 6), (uint32_t)GS_PSMT8);
    CHECK_EQ(GS_FIELD(tex0, 26, 4), 4u);
    CHECK_EQ(GS_FIELD(tex0, 34, 1), 1u);
    CHECK_EQ(GS_FIELD(tex0, 37, 14), 0x300u);
}

static int clamp255(int v)
{
    return v < 0 ? 0 : v > 255 ? 255 : v;
}

static void test_blend_map(void)
{
    /* Cs 100 with alpha 0x40, Cd 60 with alpha 0x20, FIX 0x60. */
    const int cs = 100, cd = 60, as = 0x40, ad = 0x20, fix = 0x60;
    const int val[3] = { cs, cd, 0 };
    int exact = 0, approx = 0, bad = 0;
    for (unsigned a = 0; a < 4; a++)
        for (unsigned b = 0; b < 4; b++)
            for (unsigned c = 0; c < 3; c++)
                for (unsigned d = 0; d < 4; d++) {
                    int av = val[a > 2 ? 2 : a], bv = val[b > 2 ? 2 : b], dv = val[d > 2 ? 2 : d];
                    int cv = c == 0 ? as : c == 1 ? ad : fix;
                    int expect = clamp255((((av - bv) * cv) >> 7) + dv);

                    struct gs_blend bl;
                    int r = gs_blend_map(gs_alpha(a, b, c, d, (unsigned)fix), &bl);
                    CHECK_EQ(r, bl.exact);
                    if (!r) {
                        approx++;
                        continue;
                    }
                    exact++;
                    int cfi = bl.c_source == GS_BC_SRC_ALPHA ? as : bl.c_source == GS_BC_DST_ALPHA ? ad : bl.fix;
                    float cf = (float)cfi / 128.0f;
                    float f[2], x[2] = { (float)cs, (float)cd };
                    int fac[2] = { bl.src, bl.dst };
                    for (int i = 0; i < 2; i++)
                        f[i] = fac[i] == GS_BF_ZERO ? 0 : fac[i] == GS_BF_ONE ? 1 : fac[i] == GS_BF_C ? cf : 1 - cf;
                    float out = bl.op == GS_BO_ADD ? x[0] * f[0] + x[1] * f[1]
                        : bl.op == GS_BO_SUBTRACT  ? x[0] * f[0] - x[1] * f[1]
                                                   : x[1] * f[1] - x[0] * f[0];
                    int got = clamp255((int)floorf(out));
                    if (abs(got - expect) > 1) {
                        fprintf(stderr, "blend A%u B%u C%u D%u: GS %d, fixed-function %d\n", a, b, c, d, expect, got);
                        bad++;
                    }
                }
    CHECK_EQ(bad, 0);
    CHECK(exact > 0);
    CHECK(approx > 0);
}

static void test_split_stream(void)
{
    /* The same packet fed whole and in odd-sized pieces gives the same vertices. */
    uint64_t prim = gs_prim(GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0);
    start();
    sprite(prim, 1, 2, 3, 4, 9);
    send_gif();
    gs_translator_flush(&t);
    struct gs_vertex whole[6];
    memcpy(whole, rec.v[0], sizeof(whole));

    start();
    sprite(prim, 1, 2, 3, 4, 9);
    size_t size = g.size;
    static const size_t pieces[] = { 1, 3, 7, 16, 5, 17, 2 };
    for (size_t pos = 0, i = 0; pos < size; i++) {
        size_t n = pieces[i % 7];
        if (n > size - pos)
            n = size - pos;
        gs_translator_gif(&t, 2, g.data + pos, n);
        pos += n;
    }
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 1);
    CHECK(memcmp(whole, rec.v[0], sizeof(whole)) == 0);
    CHECK(t.stats.qwords[2] == (uint64_t)(size / 16));
}

static void test_packets(void)
{
    start();
    sprite(gs_prim(GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0), 0, 0, 1, 1, 1);
    struct gs_dump_packet pk = { GS_DUMP_TRANSFER, GS_DUMP_PATH1_OLD, g.data, (uint32_t)g.size, 0 };
    CHECK_EQ(gs_translator_packet(&t, &pk), 0);
    CHECK(t.stats.qwords[1] == (uint64_t)(g.size / 16));
    pk.path = GS_DUMP_PATH2;
    CHECK_EQ(gs_translator_packet(&t, &pk), 0);
    CHECK(t.stats.qwords[2] == (uint64_t)(g.size / 16));

    static uint8_t privregs[GS_PRIV_SIZE];
    privregs[GS_PRIV_PMODE] = 1;
    struct gs_dump_packet regs = { GS_DUMP_REGISTERS, 0, privregs, GS_PRIV_SIZE, 0 };
    CHECK_EQ(gs_translator_packet(&t, &regs), 0);
    CHECK_EQ(t.privregs[GS_PRIV_PMODE], 1);

    struct gs_dump_packet vsync = { GS_DUMP_VSYNC, 0, NULL, 0, 1 };
    CHECK_EQ(gs_translator_packet(&t, &vsync), 1);
    CHECK_EQ(rec.vsyncs, 1);
    CHECK_EQ(rec.batches, 1); /* the vsync flushed both sprites as one batch */
    CHECK_EQ(rec.prims[0], 2u);
}

static void test_fst_and_fog(void)
{
    start();
    gs_translator_write(&t, GS_TEX0_1, gs_tex0(0x100, 1, GS_PSMCT32, 4, 4, 1, 0, 0, 0));
    /* UV in 12.4 texels: U 8, V 16 on a 16x16 texture is (0.5, 1.0). */
    gif_tag(&g, 2, 1, 1, (unsigned)gs_prim(GS_PRIM_SPRITE, 0, 1, 0, 0, 1, 0), FLG_PACKED, 2, 0x53);
    gif_uv(&g, 0, 0);
    gif_xyz2(&g, 0, 0, 0, 0);
    gif_uv(&g, 8 * 16, 16 * 16);
    gif_xyz2(&g, 16 * 16, 16 * 16, 0, 0);
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 1);
    CHECK(near(rec.v[0][0].s, 0) && near(rec.v[0][0].t, 0));
    CHECK(near(rec.v[0][4].s, 0.5f) && near(rec.v[0][4].t, 1.0f) && near(rec.v[0][4].q, 1.0f));
    CHECK_EQ(rec.pipe[0].tme, 1);
    CHECK_EQ(GS_FIELD(rec.pipe[0].tex0, 0, 14), 0x100u);

    /* XYZF2 in PACKED: Z in hi bits 4-27, F in hi bits 36-43. */
    start();
    gs_translator_write(&t, GS_FOGCOL, 0x123456);
    gif_tag(&g, 1, 1, 1, (unsigned)gs_prim(GS_PRIM_POINT, 0, 0, 1, 0, 0, 0), FLG_PACKED, 1, 0x4);
    gif_qword(&g, (uint64_t)(4 * 16) | (uint64_t)(4 * 16) << 32, (uint64_t)0xABCDEF << 4 | (uint64_t)0x77 << 36);
    send_gif();
    gs_translator_flush(&t);
    CHECK_EQ(rec.batches, 1);
    CHECK_EQ(rec.v[0][0].z, 0xABCDEFu);
    CHECK_EQ(rec.v[0][0].fog, 0x77);
    CHECK_EQ(rec.pipe[0].fge, 1);
    CHECK_EQ(rec.pipe[0].fogcol, 0x123456u);
}

int main(void)
{
    test_sprite_and_offset();
    test_batching();
    test_strips();
    test_flat_shading();
    test_reglist();
    test_images();
    test_tex2();
    test_blend_map();
    test_split_stream();
    test_packets();
    test_fst_and_fog();
    gs_translator_free(&t);
    return check_finish("test_gs_translate");
}
