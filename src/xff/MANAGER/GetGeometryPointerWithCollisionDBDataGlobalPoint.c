/* Parked: 17 diffs. The Original keeps point in $s4, e2 in $s5, the vertex
 * array in $s6 and e1 in $s7 (gcc 2.96 rotates them), loads the -2e-5
 * constant before storing s and t, and loads the matrix row index before
 * the matrix base. getSTDB is an inlined copy of GetSTPositionOfCollisionDB
 * whose result is unused, which leaves the Original's dead c.lt.s. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    char pad[0x54];
    int *map;
    char pad2[0x90 - 0x58];
} DBGroup;
typedef struct {
    char pad[8];
    DBGroup *groups;
    char pad2[8];
    int unk14;
    char (*verts)[0x40];
} DBData;
typedef struct {
    int layout;
    unsigned int id;
} EdgeRef;
typedef struct {
    char pad[8];
    int unk8;
    char pad2[0x4];
    Vec4 *mtx;
    char pad3[0xC];
    char *unk20;
} LayoutSub;
typedef struct {
    char pad[0xA0];
    Vec4 scale;
    char padB0[0x154 - 0xB0];
    LayoutSub sub;
    char pad2[0x184 - 0x154 - 0x24];
    char *unk184;
} Layout;
typedef struct {
    int layout;
    unsigned int id;
    float s;
    float t;
    Vec4 pos;
    char pad20[0x10];
    int mode;
} GeometryPointer;
extern Layout *GetLayoutClass(int);
extern void func_000999E0(Vec4 **, int, Layout *, int, int);
extern void func_0009AE78(Vec4 **, int, char *, int, int, DBGroup *, int, char *);

static inline void vsubA(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)\n" : : "r"(a) : "memory");
    __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n" : : "r"(b) : "memory");
    __asm__ __volatile__("vsub.xyzw vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n" : : "r"(o) : "memory");
}

static inline void vsubB(Vec4 *o, Vec4 *a)
{
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)\n" : : "r"(a) : "memory");
    __asm__ __volatile__("vsub.xyzw vf31, vf29, vf30\n"
                         "sqc2 vf31, 0x0(%0)\n" : : "r"(o) : "memory");
}

static inline void vsub(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(o) : "memory");
}

static inline void getST(float *s, float *t, Vec4 *a, Vec4 *b, Vec4 *p)
{
    float rs;
    float rt;
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "lqc2 vf7, 0x0(%4)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf8, vf6, vf5\n"
                         "vsub.w vf8, vf8, vf8\n"
                         "vopmula.xyz ACC, vf8, vf6\n"
                         "vopmsub.xyz vf9, vf6, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f2\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf5\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f3\n"
                         "div.s %0, $f2, $f3\n"
                         "vopmula.xyz ACC, vf8, vf5\n"
                         "vopmsub.xyz vf9, vf5, vf8\n"
                         "vsub.w vf9, vf9, vf9\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf7\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f2\n"
                         "vaddw.x vf10, vf0, vf0w\n"
                         "vmul.xyz vf11, vf9, vf6\n"
                         "vaddax.x ACC, vf0, vf11x\n"
                         "vmadday.x ACC, vf10, vf11y\n"
                         "vmaddz.x vf10, vf10, vf11z\n"
                         "qmfc2.ni $2, vf10\n"
                         "mtc1 $2, $f3\n"
                         "div.s %1, $f2, $f3\n"
                         : "=f"(rs), "=f"(rt) : "r"(a), "r"(b), "r"(p) : "$2", "$f2", "$f3");
    *s = rs;
    *t = rt;
}

static inline void applyMatrix(Vec4 *o, Vec4 *m, Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(o), "r"(m), "r"(v) : "memory");
}

static inline void scaleMul(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b) : "memory");
}

static inline int getSTDB(float *s, float *t, EdgeRef *edge, Vec4 *point)
{
    Vec4 e1;
    Vec4 e2;
    Vec4 d;
    Vec4 *v[4];
    Vec4 **vp = v;
    Vec4 *pe2 = &e2;
    Vec4 *pe1 = &e1;
    int sub = edge->id & 0xFFFFFF;
    int grp = (edge->id >> 24) & 0x7F;
    Layout *layout = GetLayoutClass(edge->layout);

    if ((int)edge->id < 0) {
        func_000999E0(vp, 0, layout, grp, sub);
    } else {
        LayoutSub *ls = &layout->sub;
        char *p = ls->unk20;
        DBData *db = *(DBData **)(layout->unk184 + 0x20);
        func_0009AE78(vp, 0, p + 0x28, *(int *)(p + 0x24), ls->unk8, db->groups,
                      db->unk14, db->verts[db->groups[grp].map[sub]]);
    }
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)
" : : "r"(v[1]) : "memory");
    __asm__ __volatile__("lqc2 vf30, 0x0(%0)
" : : "r"(v[0]) : "memory");
    __asm__ __volatile__("vsub.xyzw vf31, vf29, vf30
"
                         "sqc2 vf31, 0x0(%0)
" : : "r"(pe1) : "memory");
    __asm__ __volatile__("lqc2 vf29, 0x0(%0)
" : : "r"(v[2]) : "memory");
    __asm__ __volatile__("vsub.xyzw vf31, vf29, vf30
"
                         "sqc2 vf31, 0x0(%0)
" : : "r"(pe2) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "lqc2 vf6, 0x0(%1)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%2)
"
                         : : "r"(point), "r"(v[0]), "r"(&d) : "memory");
    getST(s, t, pe1, pe2, &d);
    if (*s < -0.00002f)
        return 0;
    if (*t < -0.00002f)
        return 0;
    if (*s + *t - 1.0f > 0.00002f)
        return 0;
    return 1;
}

void GetGeometryPointerWithCollisionDBDataGlobalPoint(GeometryPointer *out, EdgeRef *edge, Vec4 *point)
{
    float s;
    float t;

    getSTDB(&s, &t, edge, point);
    out->s = s;
    out->t = t;
    __asm__ __volatile__("" : : : "memory");
    out->layout = edge->layout;
    out->id = edge->id;
    if ((int)edge->id < 0) {
        Layout *l = GetLayoutClass(edge->layout);
        out->mode = 2;
        applyMatrix(&out->pos, &l->sub.mtx[((edge->id >> 24) & 0x7F) * 4], point);
        scaleMul(&out->pos, &out->pos, &l->scale);
    } else {
        out->mode = 3;
    }
}
#endif
