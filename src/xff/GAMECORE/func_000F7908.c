/* Parked: 8 diffs, same size. Remaining: register choice for x41C / -1 in the
 * way[0] setup (a2/a3 swapped), the x10 store scheduled before the pos store,
 * and the g->x60 store scheduled before n = 1 instead of into the bnez delay
 * slot.
 *
 * Called once a user path is down to its last way: when the straight segment
 * to it is blocked (ClipEdgeLinkDBFinder), and the wall faces against the move
 * or the two side probes straddle it, moves the way to 0.1 short of the hit. */

#ifdef NONMATCHING

typedef unsigned int u128 __attribute__((mode(TI)));
typedef union { u128 q; float f[4]; int i[4]; } V;

typedef struct {
    u128 pos;
    int x10;
    short area;
    short link;
    short x18;
    short x1A;
    int idx;
} Way;

typedef struct {
    V x0;
    char pad10[0x30 - 0x10];
    u128 x30;
    int x40;
    char pad44[0x50 - 0x44];
    u128 x50;
    u128 x60;
    u128 x70;
    int x80;
    int x84;
    char pad88[0xE0 - 0x88];
    int xE0;
    char padE4[0x100 - 0xE4];
    Way way[20];
    unsigned int n;
    int busy;
    char pad388[0x41C - 0x388];
    int x41C;
    int x420;
    char pad424[0x3C50 - 0x424];
    int x3C50;
} PathCtrl;

typedef struct { V p; V n; } Hit;

extern char *GetCharacterClass(int);
extern void ReconstructCollisionEdgeLinkDBVWallFinder(int, void *);
extern int ClipEdgeLinkDBFinder(Hit *, void *, void *, int, float);
extern void GetQuaternionByAxisDirZY(V *, V *, V *);
extern char *getSCRDataCtrlWork(int);
extern int _getStopCtrlModeBaseMoveWork(char *);
extern Way *getPassageWork(PathCtrl *, int);
extern V YUnitVector;

static inline Way *getWay(PathCtrl *g, unsigned int k)
{
    return k < g->n ? &g->way[k] : 0;
}

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *d, void *s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s) : "memory");
}

static inline float vecDot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline void vecOuter(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecScale(void *d, void *s, float k)
{
    __asm__ __volatile__("mfc1 $3, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $3, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s), "f"(k) : "$3", "memory");
}

static inline void quatToMatrix(V *out, V *quat)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(quat) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(&out[3]));
}

static inline void matInverse(V *dst, V *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void matApply(V *out, V *m, V *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                         : : "r"(v), "r"(m), "r"(out) : "memory");
}


typedef union { short s; int i; u128 q; } U;

static void func_000F7908(PathCtrl *g, int obj)
{
    Hit h;
    V t;
    V dir;
    Hit h1;
    Hit h2;
    V *rp;
    V a1, a2, b1, b2;
    V side;
    V r;
    V q;
    V m[4];
    V o1, o2;
    char *cls;
    int hit;

    if (g->x3C50 != 1)
        return;
    if (g->n != 1)
        return;
    cls = GetCharacterClass(obj);
    hit = 0;
    t.q = getWay(g, 0)->pos;
    t.f[1] = g->x0.f[1];
    ReconstructCollisionEdgeLinkDBVWallFinder(*(int *)(cls + 0xE40), cls + 0xE20);
    if (ClipEdgeLinkDBFinder(&h, g, &t, *(int *)(cls + 0xE40), 3.0f) == 0)
        return;
    vecSub(&dir, &t, g);
    vecNormalize(&dir, &dir);
    if (vecDot(&dir, &h.n) < -0.93969262f) {
        hit = 1;
    } else {
        vecOuter(&side, &dir, &YUnitVector);
        vecNormalize(&side, &side);
        vecScale(&side, &side, *(float *)(cls + 0x3E4));
        a1.q = g->x0.q;
        b1.q = t.q;
        a2.q = g->x0.q;
        b2.q = t.q;
        vecAdd(&a1, &a1, &side);
        vecAdd(&b1, &b1, &side);
        vecSub(&a2, &a2, &side);
        vecSub(&b2, &b2, &side);
        r.i[0] = ClipEdgeLinkDBFinder(&h1, &a1, &b1, *(int *)(cls + 0xE40), 3.0f);
        r.i[1] = ClipEdgeLinkDBFinder(&h2, &a2, &b2, *(int *)(cls + 0xE40), 3.0f);
        if (r.i[0] != 0 && r.i[1] != 0) {
            GetQuaternionByAxisDirZY(&q, &dir, &YUnitVector);
            quatToMatrix(m, &q);
            matInverse(m, m);
            matApply(&o1, m, &h1.n);
            matApply(&o2, m, &h2.n);
            if (o1.f[0] > 0.0f && o2.f[0] < 0.0f)
                hit = 1;
        }
    }
    rp = &r;
    if (hit) {
        Way *w;
        int area, idx;

        vecSub(rp, g, &h);
        vecNormalize(rp, &r);
        vecScale(&r, rp, 0.1f);
        vecAdd(&r, &h, rp);
        r.f[3] = 1.0f;
        area = g->x41C;
        idx = g->x420;
        w = &g->way[0];
        ((U *)&w->x1A)->s = 1;
        ((U *)&w->area)->s = area;
        ((U *)&w->idx)->i = idx;
        ((U *)&w->link)->s = -1;
        ((U *)&w->pos)->q = r.q;
        ((U *)&w->x18)->s = 0;
        ((U *)&w->x10)->i = 0;
        g->x60 = r.q;
        ((U *)&g->x70)->q = r.q;
        g->x80 = g->x41C;
        g->x84 = g->x420;
        g->n = 1;
        if (g->xE0 == 0) {
            char *c = GetCharacterClass(obj);
            if (*(int *)(c + 0x750) != _getStopCtrlModeBaseMoveWork(getSCRDataCtrlWork(obj) + 0x3D10)) {
                if (g->n != 0)
                    getPassageWork(g, 0)->x18 = 1;
            }
        }
    }
}

#endif
