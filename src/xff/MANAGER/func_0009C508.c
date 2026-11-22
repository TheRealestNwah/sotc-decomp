/* Parked at 22 diffs: x0 and pb.v.y swap $f4/$f5 in the loop, and the inlined water-surface
   check keeps ok in $v0 with a bnel/beql shape where the Original uses $a2, beqz and beq.
   bary must be an 8-byte aligned struct, otherwise gcc pads it to 16 bytes and the frame grows. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union Vec4 {
    struct {
        float x, y, z, w;
    } v;
    s128 q;
} Vec4;

typedef struct {
    unsigned short ids[2];
    float y;
    float x0, z0;
    float x1, z1;
    float x2, z2;
} WaterTri;

typedef struct {
    int kind;
    char pad4[0x38 - 4];
    int count;
    WaterTri *tris;
    short *table;
} WaterJudge;

typedef struct {
    char pad0[0x20];
    WaterJudge *judge;
} LayoutWork;

typedef struct {
    char pad0[0x158];
    float *m158;
    char pad15C[0x164 - 0x15C];
    float *m164;
    char pad168[0x184 - 0x168];
    LayoutWork *work;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);
extern long ClipCollisionDirectCallBackOneObj(void *, Vec4 *, Vec4 *, void *, int, int, void *, int);
extern void *GetGeometryPointerCollisionDB(void *);
extern int func_000AE060(void *);
extern int func_000AE020();
extern Vec4 D_00136F10[4];
extern Vec4 D_00136F50;

/* Barycentric s,t of p in the triangle spanned by a and b (inlined GetSTPositionOfVectorPlane). */
static inline void stpos(float *s, float *t, float *a, float *b, float *p)
{
    float rs;
    float rt;
    __asm__ __volatile__("lqc2 vf05, 0x0(%2)\n"
                         "lqc2 vf06, 0x0(%3)\n"
                         "lqc2 vf07, 0x0(%4)\n"
                         "vopmula.xyz ACC, vf05, vf06\n"
                         "vopmsub.xyz vf08, vf06, vf05\n"
                         "vsub.w vf08, vf08, vf08\n"
                         "vopmula.xyz ACC, vf08, vf06\n"
                         "vopmsub.xyz vf09, vf06, vf08\n"
                         "vsub.w vf09, vf09, vf09\n"
                         "vaddw.x vf10, vf00, vf00w\n"
                         "vmul.xyz vf11, vf09, vf07\n"
                         "vaddax.x ACC, vf00, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2 $2, vf10\n"
                         "mtc1 $2, $f2\n"
                         "vaddw.x vf10, vf00, vf00w\n"
                         "vmul.xyz vf11, vf09, vf05\n"
                         "vaddax.x ACC, vf00, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2 $2, vf10\n"
                         "mtc1 $2, $f3\n"
                         "div.s %0, $f2, $f3\n"
                         "vopmula.xyz ACC, vf08, vf05\n"
                         "vopmsub.xyz vf09, vf05, vf08\n"
                         "vsub.w vf09, vf09, vf09\n"
                         "vaddw.x vf10, vf00, vf00w\n"
                         "vmul.xyz vf11, vf09, vf07\n"
                         "vaddax.x ACC, vf00, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2 $2, vf10\n"
                         "mtc1 $2, $f2\n"
                         "vaddw.x vf10, vf00, vf00w\n"
                         "vmul.xyz vf11, vf09, vf06\n"
                         "vaddax.x ACC, vf00, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2 $2, vf10\n"
                         "mtc1 $2, $f3\n"
                         "div.s %1, $f2, $f3\n"
                         : "=f"(rs), "=f"(rt) : "r"(a), "r"(b), "r"(p) : "$2", "$f2", "$f3");
    *s = rs;
    *t = rt;
}

static inline void applyM(float *dst, float *m, float *src)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)
"
                         "lqc2 vf14, 0x0(%1)
"
                         "lqc2 vf15, 0x10(%1)
"
                         "lqc2 vf16, 0x20(%1)
"
                         "lqc2 vf17, 0x30(%1)
"
                         "vmulax.xyzw ACC, vf14, vf8x
"
                         "vmadday.xyzw ACC, vf15, vf8y
"
                         "vmaddaz.xyzw ACC, vf16, vf8z
"
                         "vmaddw.xyzw vf10, vf17, vf8w
"
                         "sqc2 vf10, 0x0(%2)" : : "r"(src), "r"(m), "r"(dst) : "memory");
}

static inline void lerp(float *dst, float *a, float *b, float r)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b), "f"(r) : "$8", "memory");
}


/* Finds the water surface triangle the segment a..b crosses and stores the crossing point in *out. */
static inline int hitwater(char *res, Vec4 *pend, Vec4 *p, void *obj, WaterJudge *judge, WaterTri *tri)
{
    int ok;
    pend->q = p->q;
    pend->v.y += -1000.0f;
    if (ClipCollisionDirectCallBackOneObj(res, p, pend, obj, 0, 0, func_000AE020, 0)) {
        int id = func_000AE060(GetGeometryPointerCollisionDB(res));
        if (judge->kind < 4 ? id != tri->ids[0] : judge->table[id] != tri->ids[1])
            ok = 0;
        else
            ok = 1;
    } else
        ok = 0;
    return ok;
}

static int func_0009C508(Vec4 *out, Vec4 *a, Vec4 *b, void *obj)
{
    Vec4 pa;
    Vec4 pb;
    Vec4 p;
    char res[0x50];
    Vec4 end;
    struct { float s, t; } __attribute__((aligned(8))) bary;
    LayoutClass *layout = GetLayoutClass(obj);
    WaterJudge *judge = layout->work->judge;
    WaterTri *tri = judge->tris;
    int i;
    Vec4 *e0 = D_00136F10;
    Vec4 *e1 = &D_00136F10[1];
    Vec4 *e2 = &D_00136F10[2];
    Vec4 *pt = &D_00136F50;

    applyM(&pa.v.x, layout->m164, &a->v.x);
    applyM(&pb.v.x, layout->m164, &b->v.x);
    for (i = 0; i < judge->count; i++, tri++) {
        float x0 = tri->x0;
        float z0 = tri->z0;
        float y;
        e1->v.x = tri->x1 - x0;
        e1->v.z = tri->z1 - z0;
        e2->v.x = tri->x2 - x0;
        e2->v.z = tri->z2 - z0;
        e0->v.x = x0;
        e0->v.z = z0;
        e0[3].v.x = tri->y;
        y = tri->y;
        if (pb.v.y < y && y < pa.v.y) {
            int ok;
            lerp(&p.v.x, &pb.v.x, &pa.v.x, (y - pa.v.y) / (pb.v.y - pa.v.y));
            pt->v.x = p.v.x - x0;
            pt->v.z = p.v.z - z0;
            stpos(&bary.s, &bary.t, &e1->v.x, &e2->v.x, &pt->v.x);
            if (bary.s < -0.00002f || bary.t < -0.00002f || bary.s + bary.t - 1.0f > 0.00002f)
                continue;
            p.v.w = 1.0f;
            applyM(&p.v.x, layout->m158, &p.v.x);
            ok = hitwater(res, &end, &p, obj, judge, tri);
            if (ok) {
                out->q = p.q;
                return 1;
            }
        }
    }
    return 0;
}
#endif
