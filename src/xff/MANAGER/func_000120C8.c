#ifdef NONMATCHING
/* Sets the current vertex's color: lit through the two VU0 matrices when lighting is fully enabled, flat otherwise. */
/* Parked: 13 diffs. Remaining: the Original keeps vtx in a3 and m1 in t2 (ours t2 and a3), so 255.0f goes through f1/a3 instead of f0/v1, and the flat branch adds g + n*64 with the operands the other way round. Declaring the five pointers inside the lit branch (color, normal, m0, m1, vtx) gets the flat branch its own lq 0x90($a2) and the Original pointer order. Not yet permuted. */
typedef int u128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x10];
    float s;
    float t;
    char pad18[8];
    u128 color;
    char pad30[0x10];
} Vert;

typedef struct {
    char pad0[0x18];
    int texture;
    char pad1C[0x80 - 0x1C];
    float normal[4];
    u128 color;
    float s;
    float t;
    char padA8[0x130 - 0xA8];
    float mat0[4][4];
    float mat1[4][4];
    char pad1B0_dummy[0];
} GlHead;

typedef union {
    GlHead h;
    struct {
        char pad[0x1B0];
        unsigned long f0 : 1;
        unsigned long f1 : 1;
        unsigned long f2 : 1;
        unsigned long f3 : 1;
    } b;
    struct {
        char pad[0x1B0];
        unsigned long all;
    } w;
    struct {
        char pad[0x220];
        u128 v[1][4];
    } v;
    struct {
        char pad[0x200];
        Vert v[1];
    } a;
    struct {
        char pad[0x41F0];
        int n;
    } n;
} GlState;

extern GlState D_00130480;

static void func_000120C8(int lit)
{
    GlState *g = &D_00130480;

    g->b.f3 = lit;
    if ((g->w.all & 0xB) == 0xB) {
        u128 *color = &g->h.color;
        float *normal = g->h.normal;
        float *m0 = g->h.mat0[0];
        float *m1 = g->h.mat1[0];
        u128 *vtx = g->v.v[0];
        u128 *dst = &vtx[g->n.n * 4];

        __asm__ __volatile__("lqc2 vf24, 0x0(%0)\n"
                             "lqc2 vf25, 0x0(%1)\n"
                             "lqc2 vf26, 0x0(%2)\n"
                             "lqc2 vf27, 0x10(%2)\n"
                             "lqc2 vf28, 0x20(%2)\n"
                             "lqc2 vf29, 0x30(%2)\n"
                             :
                             : "r"(color), "r"(normal), "r"(m0));
        __asm__ __volatile__("qmtc2.ni %2, vf30\n"
                             "vmulax.xyzw ACC, vf26, vf25x\n"
                             "vmadday.xyzw ACC, vf27, vf25y\n"
                             "vmaddaz.xyzw ACC, vf28, vf25z\n"
                             "vmaddw.xyzw vf23, vf29, vf0w\n"
                             "lqc2 vf26, 0x0(%0)\n"
                             "lqc2 vf27, 0x10(%0)\n"
                             "lqc2 vf28, 0x20(%0)\n"
                             "lqc2 vf29, 0x30(%0)\n"
                             "vmaxx.xyzw vf23, vf23, vf0x\n"
                             "vmulax.xyzw ACC, vf26, vf23x\n"
                             "vmadday.xyzw ACC, vf27, vf23y\n"
                             "vmaddaz.xyzw ACC, vf28, vf23z\n"
                             "vmaddw.xyzw vf23, vf29, vf0w\n"
                             "vmul.xyz vf24, vf24, vf23\n"
                             "vminix.xyzw vf24, vf24, vf30x\n"
                             "sqc2 vf24, 0x0(%1)\n"
                             :
                             : "r"(m1), "r"(dst), "r"(255.0f)
                             : "memory");
    } else {
        g->v.v[g->n.n][0] = g->h.color;
    }
    if (D_00130480.h.texture != 0) {
        D_00130480.a.v[D_00130480.n.n].s = D_00130480.h.s;
        D_00130480.a.v[D_00130480.n.n].t = D_00130480.h.t;
    }
    D_00130480.b.f0 = 0;
}
#endif
