typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZ(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2 %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline float lengthSquareXYZ(Vec4 *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2 $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline float distanceXYZ(const Vec4 *to, const Vec4 *from)
{
    float length;
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n"
        "lqc2 vf6, 0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n"
        "vmul.xyz vf7, vf7, vf7\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vsqrt Q, vf7w\n"
        "vwaitq\n"
        "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(length) : "r"(to), "r"(from) : "$2");
    return length;
}

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

int GAMEUTIL_get_move_limit_position3D(Vec4 *out, float *ratio, Vec4 *cur, Vec4 *target, float speed, float dt)
{
    Vec4 from;
    Vec4 diff;
    Vec4 step;
    float limit;
    float lengthSquare;

    from.q = cur->q;
    limit = speed * dt;
    subXYZ(&diff, target, &from);
    lengthSquare = lengthSquareXYZ(&diff);
    if (lengthSquare <= limit * limit) {
        out->q = target->q;
        if (ratio != 0) {
            if (dt != 0.0f) {
                speed = distanceXYZ(&from, out) / dt;
            }
            *ratio = speed;
        }
        return 0;
    }
    scaleXYZ(&step, &diff, limit / sqrtF(lengthSquare));
    addXYZ(out, &from, &step);
    if (ratio != 0) {
        *ratio = speed;
    }
    return 1;
}
