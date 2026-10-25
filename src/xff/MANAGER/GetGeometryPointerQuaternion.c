typedef int s128 __attribute__((mode(TI)));
extern float YUnitVector[];
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, float *);
extern void GetClothQuaternion(void *, void *, int, int, float);
extern void GetCollisionDBPlaneNormalZQuaternion(void *, void *);
extern void GetCollisionDBQuaternion(void *, void *);
extern void GetMotionNodeQuaternionPosToolCoord(void *, void *, void *, int, int);

static inline void multiplyQuaternion(void *out, void *left, void *right)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(left), "r"(right) : "memory");
}

void GetGeometryPointerQuaternion(s128 *out, char *geometry)
{
    struct { s128 position, quaternion; } coordinate;
    s128 rotation;
    switch (*(unsigned int *)(geometry + 0x30)) {
    case 9:
        GetClothQuaternion(out, *(void **)geometry, *(int *)(geometry + 4), 0,
                           *(float *)(geometry + 8));
        break;
    case 0:
        *out = *(s128 *)geometry;
        break;
    case 6:
        *out = **(s128 **)geometry;
        multiplyQuaternion(out, out, geometry + 0x10);
        break;
    case 7:
        *out = *(s128 *)(geometry + 0x20);
        break;
    case 5:
        GetCollisionDBPlaneNormalZQuaternion(out, geometry);
        break;
    case 1:
        GetMotionNodeQuaternionPosToolCoord(&coordinate.quaternion, &coordinate.position,
                                           *(void **)geometry,
                                           *(int *)(geometry + 4), 1);
        multiplyQuaternion(out, &coordinate.quaternion, geometry + 0x10);
        break;
    case 8:
        *out = *(s128 *)(geometry + 0x10);
        break;
    case 2:
    case 3:
    case 4:
        GetCollisionDBQuaternion(out, geometry);
        break;
    case 10:
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(out) : "memory");
        SetQuaternionByAxisRotateVWithNoRegularize(&rotation, 0x4000, YUnitVector);
        multiplyQuaternion(out, out, &rotation);
        break;
    }
}
