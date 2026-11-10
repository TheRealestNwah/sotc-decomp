typedef float Vec4[4] __attribute__((aligned(16)));

static inline float sqrtf(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

/* Parked: ~80 words off. Structure and VU blocks follow the asm; sqrt.s is an inline asm because sqrtf() adds the errno call. The original keeps d in $f1 and 1.0f in $f3 (ours: $f2) and reloads 1.0f for 1+d. */
#ifdef NONMATCHING
void GetDifferencialQuaternionWithNoRegularize(float *out, float *a, float *b, float *up)
{
    struct { Vec4 t0; Vec4 t1; } L;
    float d;
    float *p0, *p1;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vaddw.x vf7, vf0, vf0w
"
                         "vmul.xyz vf6, vf5, vf6
"
                         "vaddax.x ACC, vf0, vf6x
"
                         "vmadday.x ACC, vf7, vf6y
"
                         "vmaddz.x vf6, vf7, vf6z
"
                         "qmfc2.ni $2, vf6
"
                         "mtc1 $2, %0
"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    if (d >= 1.0f) {
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(out) : "memory");
        return;
    }
    if (d <= -1.0f) {
        float w, s;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(L.t0), "r"(up) : "memory");
        w = sqrtf(0.0f);
        s = sqrtf(1.0f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyzw vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(L.t0), "r"(s) : "memory");
        out[3] = w;
        return;
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vopmula.xyz ACC, vf5, vf6
"
                         "vopmsub.xyz vf7, vf6, vf5
"
                         "vsub.w vf7, vf7, vf7
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(L.t0), "r"(a), "r"(b) : "memory");
    p0 = L.t0;
    p1 = L.t1;
    if (d < 0.0f) {
        float m;
        __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                             "vmul.xyz vf7, vf7, vf7
"
                             "vaddy.x vf7, vf7, vf7y
"
                             "vaddz.x vf7, vf7, vf7z
"
                             "qmfc2.ni $2, vf7
"
                             "mtc1 $2, %0
"
                             : "=f"(m) : "r"(p0) : "$2");
        if (m == 0.0f) {
            float w, s;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(p1), "r"(up) : "memory");
            w = sqrtf(0.0f);
            s = sqrtf(1.0f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyzw vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(L.t1), "r"(s) : "memory");
            out[3] = d;
            return;
        }
    }
    {
        float p = d + 1.0f;
        float r, h;
        p = sqrtf(p);
        h = 0.70710677f;
        r = h / p;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyzw vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(L.t0), "r"(r) : "memory");
        out[3] = p * h;
    }
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
#else
extern void GetDifferencialQuaternionWithNoRegularize(float *out, float *a, float *b, float *up);
#endif
