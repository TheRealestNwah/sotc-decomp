extern float ZeroVector[];
extern float YUnitVector[];
extern float ZUnitVector[];
extern int CheckLegalCollisionGP(void *);
extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);
extern float *GetGeometryPointerSurfacePlane(void *);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern void GetGeometryPointerPosition(void *, void *);
extern void UpdateLayoutClassParentGeometry(char *, float *, float *);
extern void UpdateLayoutClassSimpleGeometry(char *, float);

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")
#define VU_QUAT_NORMALIZE(q) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n" \
                         "vmul.xyzw vf15, vf14, vf14\n" \
                         "vaddy.x vf15, vf15, vf15y\n" \
                         "vaddz.x vf15, vf15, vf15z\n" \
                         "vaddw.x vf15, vf15, vf15w\n" \
                         "vrsqrt Q, vf0w, vf15x\n" \
                         "vwaitq\n" \
                         "vmulq.xyzw vf15, vf14, Q\n" \
                         "sqc2 vf15, 0x0(%0)\n" \
                         : : "r"(q) : "memory")

static void func_00088858(char *obj, float time)
{
    char *layout = obj + 0x70;
    void *ground;
    float *plane;
    char *parent;
    float q[4] __attribute__((aligned(16)));
    float *rq;

    if (!*(int *)(layout + 0x124))
        return;
    ground = 0;
    if (*(signed char *)(obj + 0x367)) {
        if (!CheckLegalCollisionGP(obj + 0x130)) {
            parent = GetLayoutClass(GetGeometryPointerObject(obj + 0x130));
            if (*(int *)(parent + 0x124) && CheckLegalCollisionGP(parent + 0xC0))
                ground = parent + 0xC0;
        }
    }
    if (ground) {
        plane = GetGeometryPointerSurfacePlane(ground);
        rq = *(float **)(layout + 0x13C);
        GetDifferencialQuaternionWithNoRegularize(q, plane, YUnitVector, ZUnitVector);
        VU_QUAT_MUL(rq, q, rq);
        VU_QUAT_NORMALIZE(rq);
        GetGeometryPointerPosition(*(void **)(layout + 0x134), ground);
    } else {
        UpdateLayoutClassParentGeometry(layout, ZeroVector, ZeroVector);
    }
    UpdateLayoutClassSimpleGeometry(layout, time);
}
