typedef float Vector[4] __attribute__((aligned(16)));

static inline void subtract(Vector out, Vector a, Vector b)
{
    __asm__ __volatile__(
        "lqc2 vf4, 0(%1)\n" "lqc2 vf5, 0(%2)\n"
        "vsub.xyzw vf6, vf4, vf5\n" "sqc2 vf6, 0(%0)\n"
        : : "r"((unsigned long)out), "r"(a), "r"(b) : "memory");
}

static inline float dotXYZ(Vector a, Vector b)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf4, 0(%1)\n" "lqc2 vf5, 0(%2)\n"
        "vmul.xyz vf5, vf4, vf5\n"
        "vaddy.x vf5, vf5, vf5y\n" "vaddz.x vf5, vf5, vf5z\n"
        "qmfc2 $2, vf5\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(a), "r"(b) : "$2");
    return result;
}

static inline float squareLengthXYZ(Vector a)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf4, 0(%1)\n" "vmul.xyz vf5, vf4, vf4\n"
        "vaddy.x vf5, vf5, vf5y\n" "vaddz.x vf5, vf5, vf5z\n"
        "qmfc2 $2, vf5\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(a) : "$2");
    return result;
}

static inline void scaleAdd(Vector out, Vector direction, float t, Vector offset)
{
    __asm__ __volatile__(
        "lqc2 vf7, 0(%3)\n" "lqc2 vf4, 0(%1)\n"
        "mfc1 $8, %2\n" "qmtc2 $8, vf5\n"
        "vmulx.xyzw vf6, vf4, vf5x\n"
        "vadd.xyzw vf5, vf6, vf7\n" "sqc2 vf5, 0(%0)\n"
        : : "r"(out), "r"(direction), "f"(t), "r"(offset) : "$8", "memory");
}

static inline float lengthXYZ(Vector a)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf4, 0(%1)\n" "vmul.xyz vf5, vf4, vf4\n"
        "vaddy.x vf5, vf5, vf5y\n" "vaddz.x vf5, vf5, vf5z\n"
        "vsqrt Q, vf5x\n" "vwaitq\n" "vaddq.x vf5, vf0, Q\n"
        "qmfc2 $2, vf5\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(a) : "$2");
    return result;
}

float CalcDistancePointAndLine(Vector point, Vector origin, Vector direction)
{
    Vector perpendicular;
    Vector offset;
    float dot;
    float squareLength;
    float t;
    subtract(offset, origin, point);
    dot = dotXYZ(offset, direction);
    squareLength = squareLengthXYZ(direction);
    t = -dot / squareLength;
    scaleAdd(perpendicular, direction, t, offset);
    return lengthXYZ(perpendicular);
}
