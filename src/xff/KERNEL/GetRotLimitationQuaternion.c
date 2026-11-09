typedef float Vec4[4] __attribute__((aligned(16)));

extern Vec4 XUnitVector;
extern Vec4 YUnitVector;
extern Vec4 ZUnitVector;
extern void GetEulerYXZFromQuaternion(float *, float *);
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

/* Parked: ~195 words off (size 208 vs 220). Structure follows the asm (YXZ euler, clamp each axis, rebuild via Y/X/Z rotations); the original keeps extra float copies of the tested angle and different saved registers for out/lim. */
#ifdef NONMATCHING
int GetRotLimitationQuaternion(float *out, float *q, float *lim)
{
    struct { Vec4 e; Vec4 t0; Vec4 t1; Vec4 t2; } L;
    int changed = 0;
    int used;
    float x, y, z, tx, ty, tz;

    GetEulerYXZFromQuaternion(L.e, q);
    x = L.e[0];
    tx = x;
    if (x < 0.0f ? lim[0] < -x : lim[0] < x) {
        if (0.0f < tx)
            L.e[0] = lim[0];
        else {
            x = -lim[0];
            L.e[0] = x;
        }
        x = L.e[0];
        changed = 1;
    }
    y = L.e[1];
    ty = y;
    if (y < 0.0f ? lim[1] < -y : lim[1] < y) {
        if (0.0f < ty)
            L.e[1] = lim[1];
        else {
            y = -lim[1];
            L.e[1] = y;
        }
        y = L.e[1];
        changed = 1;
    }
    z = L.e[2];
    tz = z;
    if (z < 0.0f ? lim[2] < -z : lim[2] < z) {
        if (0.0f < tz)
            L.e[2] = lim[2];
        else {
            z = -lim[2];
            L.e[2] = z;
        }
        z = L.e[2];
        changed = 1;
    }
    used = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(out) : "memory");
    if (y != 0.0f) {
        short a = (short)(y * 32768.0f / 3.14159274f);
        SetQuaternionByAxisRotateVWithNoRegularize(L.t0, -a, YUnitVector);
        quatMul(out, L.t0);
        used = 1;
    }
    if (x != 0.0f) {
        short a = (short)(x * 32768.0f / 3.14159274f);
        SetQuaternionByAxisRotateVWithNoRegularize(L.t1, -a, XUnitVector);
        quatMul(out, L.t1);
        used = 1;
    }
    if (z != 0.0f) {
        short a = (short)(z * 32768.0f / 3.14159274f);
        SetQuaternionByAxisRotateVWithNoRegularize(L.t2, -a, ZUnitVector);
        quatMul(out, L.t2);
        used = 1;
    }
    if (used) {
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)
"
                             "vmul.xyzw vf15, vf14, vf14
"
                             "vaddy.x vf15, vf15, vf15y
"
                             "vaddz.x vf15, vf15, vf15z
"
                             "vaddw.x vf15, vf15, vf15w
"
                             "vrsqrt Q, vf0w, vf15x
"
                             "vwaitq
"
                             "vmulq.xyzw vf15, vf14, Q
"
                             "sqc2 vf15, 0x0(%0)
"
                             : : "r"(out) : "memory");
    }
    return changed;
}
#else
extern int GetRotLimitationQuaternion(float *out, float *q, float *lim);
#endif
