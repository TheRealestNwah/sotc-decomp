/* 20 diffs, same length (192 words). Vertical plane through the line a-b: n = normalize(a x b), c = n x YUnitVector, out = normalize(c x n), or normalize(n x a) when flag is 0 or c is degenerate. Completes the D terms of n (through p) and out (through the inline 3-plane intersection of a, b, n). Returns 1 for a degenerate a x b, or when n is nearly horizontal-normal (|n.y| < 0.01) with a.y, b.y >= 0 and dot(a, b) <= 0. Only the float scheduling of the inlined intersection differs: the Original loads a[1] before b[3] and issues div.s two multiplies later. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern float YUnitVector[4];

static inline void crossXYZ(float *out, const float *a, const float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float lengthSquareXYZ(const float *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

static inline void normalizeXYZ(float *out, const float *a)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a) : "memory");
}

static inline void completePlaneD2(float *plane, const float *p)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%0)\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf5, vf4, vf5\n"
        "vaddy.x vf5, vf5, vf5y\n"
        "vaddz.x vf5, vf5, vf5z\n"
        "vsubw.xyzw vf6, vf0, vf0w\n"
        "vsubx.w vf4, vf6, vf5x\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(plane), "r"(p));
}

static inline void completePlaneD(float *plane, const float *p)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%0)\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf5, vf4, vf5\n"
        "vaddy.x vf5, vf5, vf5y\n"
        "vaddz.x vf5, vf5, vf5z\n"
        "vsubw.xyzw vf6, vf0, vf0w\n"
        "vsubx.w vf4, vf6, vf5x\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(plane), "r"(p) : "memory");
}

static inline void crossPositionOf3Plane(float *out, float *a, float *b, float *c)
{
    float A, B, C, D, E, F, ax, inv;

    A = b[1] * c[2] - c[1] * b[2];
    B = b[0] * c[2] - c[0] * b[2];
    C = b[0] * c[1] - c[0] * b[1];
    ax = a[0] * A;
    F = b[0] * c[3] - c[0] * b[3];
    E = b[3] * c[1] - c[3] * b[1];
    D = b[3] * c[2] - c[3] * b[2];
    inv = 1.0f / (ax - a[1] * B + a[2] * C);
    out[0] = (a[1] * D - a[3] * A - a[2] * E) * inv;
    out[1] = (a[3] * B - a[0] * D - a[2] * F) * inv;
    out[2] = (a[1] * F + a[0] * E - a[3] * C) * inv;
    out[3] = 1.0f;
}

static inline float dotXYZ(const float *a, const float *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

#ifdef NONMATCHING
int GetVirtualVerticalPlane(float *out, float *a, float *b, float *p, int flag)
{
    Vec4 n;
    Vec4 c;
    Vec4 x;
    int r;

    crossXYZ(n.f, a, b);
    if (lengthSquareXYZ(n.f) < 0.001f) {
        return 1;
    }
    normalizeXYZ(n.f, n.f);
    crossXYZ(c.f, n.f, YUnitVector);
    if (flag == 0 || lengthSquareXYZ(c.f) < 0.001f) {
        crossXYZ(out, n.f, a);
    } else {
        crossXYZ(out, c.f, n.f);
    }
    normalizeXYZ(out, out);
    completePlaneD(n.f, p);
    crossPositionOf3Plane(x.f, a, b, n.f);
    completePlaneD2(out, x.f);
    r = 0;
    if (n.f[1] < 0.0f ? -0.01f < n.f[1] : n.f[1] < 0.01f) {
        if (0.0f <= a[1] && 0.0f <= b[1] && dotXYZ(a, b) <= 0.0f) {
            r = 1;
        }
    }
    return r;
}
#endif
