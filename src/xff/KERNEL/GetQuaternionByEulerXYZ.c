typedef float Vec4[4] __attribute__((aligned(16)));

extern Vec4 XUnitVector;
extern Vec4 YUnitVector;
extern Vec4 ZUnitVector;
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

static inline void quatMul(float *q, float *r)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
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
                         : : "r"(q), "r"(r) : "memory");
}

void GetQuaternionByEulerXYZ(float *q, float x, float y, float z)
{
    Vec4 t[3];
    short sy;
    short sx;
    int changed = 0;
    short sz;

    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(q) : "memory");
    if (x != 0.0f) {
        {
            float *a = t[0];
            sx = (short)(x * 32768.0f / 3.14159274f);
            SetQuaternionByAxisRotateVWithNoRegularize(a, -sx, XUnitVector);
            __asm__("" : "+r"(a));
        }
        quatMul(q, t[0]);
        changed = 1;
    }
    if (y != 0.0f) {
        {
            float *a = t[1];
            sy = (short)(y * 32768.0f / 3.14159274f);
            __asm__("" : "+r"(a));
            SetQuaternionByAxisRotateVWithNoRegularize(a, -sy, YUnitVector);
        }
        quatMul(q, t[1]);
        changed = 1;
    }
    if (z != 0.0f) {
        {
            float *a = t[2];
            sz = (short)(z * 32768.0f / 3.14159274f);
            __asm__("" : "+r"(a));
            SetQuaternionByAxisRotateVWithNoRegularize(a, -sz, ZUnitVector);
        }
        quatMul(q, t[2]);
        changed = 1;
    }
    if (changed) {
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                             "vmul.xyzw vf15, vf14, vf14\n"
                             "vaddy.x vf15, vf15, vf15y\n"
                             "vaddz.x vf15, vf15, vf15z\n"
                             "vaddw.x vf15, vf15, vf15w\n"
                             "vrsqrt Q, vf0w, vf15x\n"
                             "vwaitq\n"
                             "vmulq.xyzw vf15, vf14, Q\n"
                             "sqc2 vf15, 0x0(%0)\n"
                             : : "r"(q) : "memory");
    }
}
