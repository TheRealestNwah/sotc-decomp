typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));

extern char *GetSCRCharaAIWorkPtr(void);
extern void *memset(void *, int, unsigned int);
extern float iosGetRandom(void);
extern void iosRotMatrixY(void *, float);
extern char *GetLayoutClass(int);
extern char *getSCRDataCtrlWork(int);
extern void SCRGetCharNodePos(void *, int, int);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void SCRSetupMissile1(int, void *, void *, int);

static inline void applyMatrix(void *out, void *m, void *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void subXYZW(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void scaleVector(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void dirNormalize(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "vmul.xyz vf5, vf6, vf6\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsqrt Q, vf5x\n"
                         "vwaitq\n"
                         "vaddq.x vf5, vf0, Q\n"
                         "vdiv Q, vf0w, vf5x\n"
                         "vsub.xyzw vf7, vf0, vf0\n"
                         "vwaitq\n"
                         "vmulq.xyz vf7, vf6, Q\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b));
}

static void func_000C9DA0(int obj, int unused, int node)
{
    union { Vec4 v; s128 q; } pos;
    Vec4 m[4];
    Vec4 dir;
    Vec4 np;
    Vec4 dz;
    char *w;
    float r;

    w = GetSCRCharaAIWorkPtr();
    memset(&pos, 0, 0x10);
    pos.v.w = 1.0f;
    switch (*(int *)(w + 0x41C4)) {
    case 0:
        r = 3.5f;
        goto rnd;
    case 1:
        r = 2.5f;
        goto rnd;
    case 2:
        r = 1.5f;
    rnd:
        pos.v.x = iosGetRandom() * r;
        pos.v.z = iosGetRandom() * r;
        break;
    }
    if (*(int *)(w + 0x41C4) != 3) {
        float a = iosGetRandom() * 3.1415925026f;

        iosRotMatrixY(m, a + a);
        applyMatrix(&pos, m, &pos);
        subXYZW(&dir, *(void **)(GetLayoutClass(obj) + 0x134), *(void **)(*(char **)(w + 0x408C) + 0x134));
        dir.y = 0.0f;
        vecNormalize(&dir);
        scaleVector(&dir, &dir, 5.0f);
        addXYZ(&dir, &dir, *(void **)(*(char **)(w + 0x408C) + 0x134));
        addXYZ(&pos, &pos, &dir);
        pos.v.w = 1.0f;
    } else {
        pos.q = **(s128 **)(*(char **)(getSCRDataCtrlWork(obj) + 0x407C) + 0x134);
    }
    SCRGetCharNodePos(&np, obj, node);
    dirNormalize(&dz, &pos, &np);
    GetQuaternionByAxisDirZY(&dir, &dz, &dz);
    SCRSetupMissile1(obj, &np, &dir, 0);
}
