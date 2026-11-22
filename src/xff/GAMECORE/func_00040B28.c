typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern int *DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void);
extern long nico_GetGeometryPointerAttr(int);
extern char *GetLayoutClass(void *);
extern Vec4 *GetGeometryPointerSurfacePlane(int);
extern void *GetGeometryPointerObject(int);
extern int execCondition(void *, void *);
extern void SendCharaAttackMsg(void *, void *, int, int, float);
extern float iosGetCosf(float);

static inline char *dldTable(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
}

static inline int dldCount(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? t[3] : 0;
}

static inline char *dldPtr(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static int func_00040B28(void *obj, int geo, long mask, long match, unsigned int *h, float angle)
{
    char *aiw;
    long attr;
    int ok;
    char *lc;
    Vec4 up;
    union { s128 q; Vec4 v; } u;
    float c;
    float d;
    float m1;
    void *go;
    unsigned int *e;
    int cnt;
    int i;
    char *a;
    char *b;

    aiw = GetSCRCharaAIWorkPtr();
    attr = nico_GetGeometryPointerAttr(geo);
    ok = 1;
    if (mask != -1) {
        long m = attr & mask;
        if (match != -1)
            ok = (match == m);
        else
            ok = (m != 0);
    }
    if (ok != 0) {
    lc = GetLayoutClass(obj);
    u.q = *(s128 *)GetGeometryPointerSurfacePlane(geo);
    u.v.y = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&u.v) : "memory");

    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&u.v), "r"(-1.0f) : "memory");
    u.v.w = -1.0f;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&up), "r"(*(void **)(lc + 0x13C)) : "memory");
    c = iosGetCosf(angle * 0.0174532925f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(&up), "r"(&u.v) : "$2", "memory");
    if (!(c < d))
        return 0;
    go = GetGeometryPointerObject(geo);
    e = (unsigned int *)dldTable(h);
    if (e != 0) {
    cnt = dldCount(h);
    for (i = 0; i < cnt; i++, e += 3) {
        a = dldPtr(&e[0]);
        b = dldPtr(&e[1]);
        if (a == 0 || b == 0)
            continue;
        if (GetLayoutClass(go) == 0 || *(char **)(GetLayoutClass(go) + 0x1A4) != b)
            continue;
        if (GetLayoutClass(*(void **)(aiw + 0x41C8)) == 0 || *(char **)(GetLayoutClass(*(void **)(aiw + 0x41C8)) + 0x1A4) != a)
            continue;
        if (execCondition(obj, &e[2])) {
            SendCharaAttackMsg(obj, go, geo, -1, 0.0f);
            return 1;
        }
    }
    }
    }
    return 0;
}
