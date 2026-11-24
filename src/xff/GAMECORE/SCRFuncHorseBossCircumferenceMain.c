typedef float Vec4[4] __attribute__((aligned(16)));

typedef union { float f; int i; void *p; } FU;
extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void setAttainmentPosAndDirPosAndLock(void *, float *, void *);
extern int GetDebugDispType(void);
extern void glLoadIdentity(void);
extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(float *, int, float);
extern void iosTransMatrixF(float *, float *, float, float, float);
extern void iosScaleMatrixV(float *, float *, float *);
extern void DebugDispBox(float *, int);

static inline void vzero(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline void quatPosToMatrix(float *out, float *quat, float *pos)
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
                         : : "r"(out), "r"(quat));
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos));
}
static inline void matInverse(float *dst, float *src)
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
static inline void matApply(float *out, float *m, float *v)
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

void SCRFuncHorseBossCircumferenceMain(void *obj, float r, float lo, float hi, float yofs)
{
    struct {
        Vec4 inv[4];
        Vec4 m[4];
        Vec4 rel;
        Vec4 v;
        Vec4 out;
        Vec4 sc;
    } L;
    void *e;
    char *w;
    char *l;
    float rr;
    float s;
    float half;

    e = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    w = getSCRDataCtrlWork(obj);
    if (e == 0)
        return;
    l = GetLayoutClass(e);
    rr = r * *(float *)(l + 0x98);
    vzero(L.v);
    quatPosToMatrix(L.m[0], (float *)(GetCharacterClass(e) + 0x470), *(float **)(l + 0x134));
    matInverse(L.inv[0], L.m[0]);
    matApply(L.rel, L.inv[0], *(float **)(*(char **)(w + 0x407C) + 0x134));
    s = *(float *)(l + 0x98);
    lo = lo * s;
    hi = hi * s;
    if (L.rel[2] <= lo) {
        L.v[2] = lo - rr;
    } else if (hi <= L.rel[2]) {
        L.v[2] = hi + rr;
    } else if (0.0f <= L.rel[0]) {
        L.v[0] = rr;
        L.v[2] = (lo + hi) * 0.5f;
    } else {
        L.v[0] = -rr;
        L.v[2] = (lo + hi) * 0.5f;
    }
    matApply(L.out, L.m[0], L.v);
    /* The union store may alias the 0x407C load, keeping it after the store. */
    ((FU *)&L.out[1])->f += yofs;
    setAttainmentPosAndDirPosAndLock(w, L.out, *(void **)(*(char **)(w + 0x407C) + 0x134));
    if (GetDebugDispType() == 6) {
        half = (hi - lo) * 0.5f;
        L.sc[0] = r;
        L.sc[1] = 1.0f;
        L.sc[2] = half;
        L.sc[3] = 1.0f;
        glLoadIdentity();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        DebugDispRadiusIndicator(L.out, 5, 1.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        iosTransMatrixF(L.m[0], L.m[0], 0.0f, 0.0f, lo + half);
        iosScaleMatrixV(L.m[0], L.m[0], L.sc);
        DebugDispBox(L.m[0], 4);
    }
}
