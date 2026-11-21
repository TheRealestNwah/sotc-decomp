/* Parked: 10 diffs. Remaining: $s5/$s6 hold m and cls+0xE20 swapped, and the t0/mov.s argument order of the getCompleteFittingPlaneFromStabGPWithSlopeLimit call. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) F4;
typedef union { s128 q; F4 f; } Vec4;

extern int DldSysUndefSymbol;
extern s128 ZeroVector;
extern Vec4 ZeroPoint;
extern void UnlinkSecureParentInfo(void *);
extern void charrootdyn_updateCharacterClassParentGeometry(void *, void *, void *);
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

extern void charrootdyn_getCompleteFittingYQFromYDir(void *, void *, void *);
extern int charrootdyn_getCompleteFittingPlaneFromStabGPWithSlopeLimit(void *, void *, void *, void *, void *, void *, float, float);
extern void SetCharacterClassRootQuaternion(void *, void *);
extern void GetGeometryPointerPosition(void *, void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern int charrootdyn_clipNoStopCollisionFinder(void *, void *, void *, void *);
extern void CopyGeometryPointer(void *, void *);
extern void charrootdyn_getRegularColFinderPosition(void *, void *, void *, void *);
extern int charrootdyn_getCollisionDB(void *, void *, void *, void *, void *, int, float);
extern void func_0006D2D0(void *, void *);

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void subXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void subXYZW(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void dirY(void *out, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void conjugate(void *out, void *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void rotateVector(void *out, void *q, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(q), "r"(v) : "memory");
}

typedef union { char g[0x50]; Vec4 r; struct { Vec4 v; F4 f; } cm; } Tmp;
static inline void startxzfit_common(char *c, Tmp *u)
{
    char *e;

    quatMul(c + 0x470, *(void **)(c + 0x13C), c + 0x490);
    ((Vec4 *)(c + 0xAB0))->q = ZeroVector;
    e = dldElem((unsigned int *)(*(char **)(c + 0x1C0) + 0xC));
    if (e != 0 && (*(unsigned int *)(e + 0x14) >> 1) & 1) {
        u->cm.f.x = *(float *)(e + 0x18);
        u->cm.f.y = *(float *)(e + 0x1C);
        u->cm.f.z = *(float *)(e + 0x20);
        u->cm.f.w = *(float *)(e + 0x24);
        u->cm.v.f = u->cm.f;
        ((Vec4 *)(c + 0xB40))->q = u->cm.v.q;
    } else {
        zeroVector(c + 0xB40);
    }
    *(int *)(c + 0xB50) = 0;
    UnlinkSecureParentInfo(c + 0xAC0);
    zeroVector(c + 0xB30);
}

void motrootdyn_startxzfit(void *m, char *cls)
{
    Vec4 plane;
    Vec4 pd;
    char mode[0x10];
    Vec4 pos;
    Vec4 t;
    Vec4 dy;
    Tmp u;
    int *h = (int *)(cls + 0x1C0);
    char *gp = cls + 0xC0;
    char *db = cls + 0xE20;
    Vec4 *q = *(Vec4 **)(cls + 0x13C);

    if (*(int *)(cls + 0xFBC) != 0) {
        float lim;
        ParentLayoutObj(m, cls + 0xF70);
        charrootdyn_getCompleteFittingYQFromYDir(q, GetGeometryPointerSurfacePlane(gp), q);
        lim = *(float *)(cls + 0x40C);
        charrootdyn_getNoLimitMode(mode, cls);
        charrootdyn_getCompleteFittingPlaneFromStabGPWithSlopeLimit(&plane, &pd, gp, db, q, mode, lim, lim);
        charrootdyn_getCompleteFittingYQFromYDir(q, &plane, q);
        SetCharacterClassRootQuaternion(cls, q);
        charrootdyn_getLocalOffsetFromParentGP(cls + 0x6D0, q, *(void **)(cls + 0x134), gp);
    } else if (*(int *)(cls + 0x124) != 0) {
        GetGeometryPointerPosition(&pos, gp);
        addXYZ(*(void **)(cls + 0x134), &pos, cls + 0x6D0);
        *(float *)(cls + 0x6D4) = GetPointDistanceFromPlane(GetGeometryPointerSurfacePlane(gp), *(void **)(cls + 0x134));
        { float z = 0.0f; *(float *)(cls + 0x6D8) = z; *(float *)(cls + 0x6D0) = z; }
        dirY(&dy, q);
        subXYZ(&t, *(void **)(cls + 0x134), &dy);
        if (charrootdyn_clipNoStopCollisionFinder(u.g, *(void **)(cls + 0x134), &t, db) != 0)
            CopyGeometryPointer(gp, u.g);
    } else if (*(int *)(cls + 0xF3C) != 0) {
        char *p = cls + 0xEF0;
        GetGeometryPointerPosition(&t, p);
        subXYZW(&dy, *(void **)(cls + 0x134), &t);
        charrootdyn_getCompleteFittingYQFromYDir(q, GetGeometryPointerSurfacePlane(p), q);
        { F4 *o = (F4 *)(cls + 0x6D0);
        conjugate(&u.r, q);
        rotateVector(o, &u.r, &dy);
        o->w = 0;
        { float y = o->y; if (!(y > 0.1f)) y = 0.1f; o->y = y; }
        }
        ParentLayoutObj(m, p);
    } else {
        charrootdyn_getRegularColFinderPosition(cls + 0x4C0, cls, q, *(void **)(cls + 0x134));
        charrootdyn_getCollisionDB(db, (char *)*(int *)(cls + 0xE38) + *(short *)(cls + 0x370) * 4, m, cls + 0x4C0, cls + 0x4D0, *h, *(float *)(cls + 0xE34));
        func_0006D2D0(m, cls);
    }
    startxzfit_common(cls, &u);
}
#endif
