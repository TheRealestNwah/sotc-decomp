typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern s128 ZeroVector;
extern char *GetCharacterClass(void *);
extern void UnlinkSecureParentInfo(void *);
extern void LinkSecureParentInfoByGP(void *, void *);
extern int charrootdyn_getNipPlaneStatus(void *, void *, void *);
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern void GetCollisionDBCurrentPointOnLastPlane(Vec4 *, void *, Vec4 *);
extern void ParentLayoutObj(void *, void *);
extern Vec4 *GetGeometryPointerSurfacePlane(void *);
extern void GetGeometryPointerSurfaceAttribute(long long *, void *);
extern float GetPlaneSlopeDegree(Vec4 *);
extern void GetPlaneZTopYPlaneCoordQuaternion(Vec4 *, Vec4 *);
extern float GetTurnYAngleFromGlobalDir(Vec4 *, Vec4 *);
extern void SetLayoutClassRootQuaternion(char *, void *);
extern void charrootdyn_getLocalOffsetFromParentGPwithGPCoordinate(float *, void *, void *);

static inline void vecSubXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void vecScale(void *dst, void *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecZero(void *p)
{
    __asm__ __volatile__("sq $0, 0x0(%0)" : : "r"(p) : "memory");
}
static inline void quat_dir(void *out, void *q)
{
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
        : : "r"(out), "r"(q) : "memory");
}

static inline void CopyVector3(float *dst, float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

static inline float turnAngle(Vec4 *plane, void *q)
{
    Vec4 coord, dir;

    GetPlaneZTopYPlaneCoordQuaternion(&coord, plane);
    quat_dir(&dir, q);
    return GetTurnYAngleFromGlobalDir(&coord, &dir);
}

void charrootdyn_setLandingStatus(void *obj, void *gp, float scale)
{
    char *c = GetCharacterClass(obj);
    Vec4 pt, ofs, pos;
    Vec4 *plane;

    *(s128 *)(c + 0x6D0) = ZeroVector;
    *(c + 0x10A1) = 0;
    *(c + 0xC96) = 0;
    vecZero(c + 0xAB0);
    *(c + 0xC95) = 0;
    vecZero(c + 0x9D0);
    UnlinkSecureParentInfo(c + 0xF70);
    LinkSecureParentInfoByGP(c + 0xF70, gp);
    *(int *)(c + 0xFC0) = 0;
    charrootdyn_getNipPlaneStatus(c + 0xFD0, c, gp);
    GetGeometryPointerPosition(&pos, gp);
    GetCollisionDBCurrentPointOnLastPlane(&pt, gp, &pos);
    vecSubXYZ(&ofs, &pos, &pt);
    vecScale(&ofs, &ofs, scale);
    vecSubXYZ(c + 0x540, &ofs, c + 0x30);
    *(c + 0x35D) = 1;
    ParentLayoutObj(obj, gp);
    plane = GetGeometryPointerSurfacePlane(gp);
    {
        long long attr;
        GetGeometryPointerSurfaceAttribute(&attr, gp);
        *(long long *)(c + 0x698) = *(long long *)(c + 0x690) = attr;
    }
    *(float *)(c + 0x6B4) = GetPlaneSlopeDegree(plane);
    *(s128 *)(c + 0x6A0) = plane->q;
    *(float *)(c + 0x6BC) = turnAngle(plane, *(void **)(c + 0x13C));
    SetLayoutClassRootQuaternion(c, *(void **)(c + 0x13C));
    {
        float local[4];
        charrootdyn_getLocalOffsetFromParentGPwithGPCoordinate(local, gp, *(void **)(c + 0x134));
        CopyVector3((float *)(c + 0xA80), local);
    }
}
