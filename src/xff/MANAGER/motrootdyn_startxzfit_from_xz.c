/* Refreshes the parent geometry, parents the layout object to the character's F70 geometry when its surface plane matches the C0 one (|dot - 1| < 0.001), applies the limit-mode overrides from the dld flag word, fits the root quaternion, takes the parent offset, runs the shared startxzfit setup and clears the Y of the copied B30 offset. */
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) F4;
typedef union { s128 q; F4 f; } Vec4;

extern int DldSysUndefSymbol;
extern s128 ZeroVector;
extern Vec4 ZeroPoint;
extern void UnlinkSecureParentInfo(void *);
extern void charrootdyn_updateCharacterClassParentGeometry(void *, void *, void *);
extern char *GetCharacterClass(void *);
extern void *GetGeometryPointerSurfacePlane(void *);
extern void ParentLayoutObj(void *, void *);
extern void charrootdyn_getLimitMode(void *, void *);
extern void charrootdyn_getForceNoLimitMode(void *, void *);
extern void charrootdyn_getNoLimitMode(void *, void *);
extern void charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(void *, void *, void *, void *, void *, float, float);
extern void SetLayoutClassRootQuaternion(void *, void *);
extern void charrootdyn_getLocalOffsetFromParentGP(void *, void *, void *, void *);

static inline void *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    unsigned int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return (void *)(t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3]);
    return 0;
}

static inline void quatMul(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void zeroVector(void *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

static inline float innerProduct(void *a, void *b)
{
    register float r __asm__("$2");
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(r) : "r"(a), "r"(b));
    {
        register float f __asm__("$f0") = r;
        __asm__ __volatile__("" : "+f"(f));
        return f;
    }
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static inline void startxzfit_common(char *c)
{
    char *e;

    quatMul(c + 0x470, *(void **)(c + 0x13C), c + 0x490);
    ((Vec4 *)(c + 0xAB0))->q = ZeroVector;
    e = dldElem((unsigned int *)(*(char **)(c + 0x1C0) + 0xC));
    if (e != 0 && (*(unsigned int *)(e + 0x14) >> 1) & 1) {
        Vec4 v;
        F4 f;
        f.x = *(float *)(e + 0x18);
        f.y = *(float *)(e + 0x1C);
        f.z = *(float *)(e + 0x20);
        f.w = *(float *)(e + 0x24);
        v.f = f;
        ((Vec4 *)(c + 0xB40))->q = v.q;
    } else {
        zeroVector(c + 0xB40);
    }
    *(int *)(c + 0xB50) = 0;
    UnlinkSecureParentInfo(c + 0xAC0);
    zeroVector(c + 0xB30);
}

void motrootdyn_startxzfit_from_xz(void *m, char *cls)
{
    char mode[0x10];
    char *cc;
    unsigned int *e;
    

    charrootdyn_updateCharacterClassParentGeometry(cls, &ZeroPoint, cls + 0x6D0);
    cc = GetCharacterClass(m);
    if (*(int *)(cc + 0xFBC) != 0) {
        void *p0 = GetGeometryPointerSurfacePlane(cc + 0xC0);
        void *p1 = GetGeometryPointerSurfacePlane(cc + 0xF70);
        float d = ABS(innerProduct(p0, p1) - 1.0f);
        if (d < 0.001f)
            ParentLayoutObj(m, cc + 0xF70);
    }
    e = dldElem((unsigned int *)(*(char **)(cls + 0x1C0) + 0xC));
    charrootdyn_getLimitMode(mode, cls);
    if (e != 0) {
        if (*e & 1)
            charrootdyn_getForceNoLimitMode(mode, cls);
        if ((*e >> 1) & 1)
            charrootdyn_getNoLimitMode(mode, cls);
        if ((*e >> 2) & 1) {
            int (*cb)(void *) = *(int (**)(void *))(cls + 0xC30);
            if (cb != 0 && *(int *)(cls + 0x124) != 0 && cb(cls + 0xC0) == 0)
                charrootdyn_getForceNoLimitMode(mode, cls);
        }
    }
    charrootdyn_getCompleteFittingYQFromStabGPWithSlopeLimit(*(void **)(cls + 0x13C), cls + 0xC0, cls + 0xE20, *(void **)(cls + 0x13C), mode, *(float *)(cls + 0x40C), *(float *)(cls + 0x40C));
    SetLayoutClassRootQuaternion(cls, *(void **)(cls + 0x13C));
    charrootdyn_getLocalOffsetFromParentGP(cls + 0x6D0, *(void **)(cls + 0x13C), *(void **)(cls + 0x134), cls + 0xC0);
    startxzfit_common(cls);
    ((Vec4 *)(cls + 0xB30))->q = ((Vec4 *)(cls + 0x6D0))->q;
    ((Vec4 *)(cls + 0xB30))->f.y = 0.0f;
    ((Vec4 *)(cls + 0x6D0))->f.z = ((Vec4 *)(cls + 0xB30))->f.y;
    ((Vec4 *)(cls + 0x6D0))->f.x = ((Vec4 *)(cls + 0xB30))->f.y;
}
