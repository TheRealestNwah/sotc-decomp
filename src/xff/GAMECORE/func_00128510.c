/* Parked: 158 diffs, same size (incl. the split tail func_001287C0). Cubic Hermite sample along a 32-entry ring of 0x30-byte control points (position at +0, tangent seed at +0x10, derivative at +0x20; head/current index at +0x604/+0x608, segment length at +0x600, flag bytes at +0x60D): finds the entry for the current index, and if the query distance t is below the accumulated distance d, wraps rem+t through iosFloatModulo, clamps u to [0,1], builds the four basis weights (3u^2-2u^3 form) and writes position (out, w = 1.0) and normalised blended tangent (tan), returning 1; otherwise advances the current index and d by one segment until 0x1F. VU0 runs are inline asm. Remaining: not diffed in detail yet. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern float iosFloatModulo(float, float);

static inline float vlen2(void *a, void *b)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=&r"(bits)
                         : "r"(a), "r"(b)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(bits));
    return f;
}

#define SCALE(src, dst, f)                                      \
    do {                                                        \
        int bits_;                                              \
        __asm__("mfc1 %0, %1" : "=r"(bits_) : "f"(f));          \
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"              \
                             "qmtc2.ni %1, vf6\n"               \
                             "vmulx.xyzw vf5, vf5, vf6x\n"      \
                             "sqc2 vf5, 0x0(%2)\n"              \
                             :                                  \
                             : "r"(src), "r"(bits_), "r"(dst)   \
                             : "memory");                       \
    } while (0)

#define ADD3(a, b, d)                                           \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"                  \
                         "lqc2 vf6, 0x0(%1)\n"                  \
                         "vadd.xyz vf5, vf5, vf6\n"             \
                         "sqc2 vf5, 0x0(%2)\n"                  \
                         :                                      \
                         : "r"(a), "r"(b), "r"(d)               \
                         : "memory")

static int func_00128510(char *out, char *tan, char *S, char *pos, float t)
{
    struct {
        float b0, b1, b2, b3;
        Vec tmp;
    } L __attribute__((aligned(16)));
    int head;
    int cur;
    int idx;
    int j;
    float seg;
    float d;
    float rem;
    float u;
    float u2;
    float u3;
    float k;
    float one;
    char *p0;
    char *p1;
    int bits;

    head = *(int *)(S + 0x604);
    cur = *(int *)(S + 0x608);
    idx = (head - cur + 0x20) % 0x20;
    d = vlen2(S + idx * 0x30, pos);
    seg = *(float *)(S + 0x600);
    rem = seg - d;
    if (*(S + idx + 0x60D) == 0 && cur < 0x1F) {
        do {
            idx = (head - cur + 0x20) % 0x20;
            if (t < d) {
                u = iosFloatModulo(rem + t, seg) / *(float *)(S + 0x600);
                if (!(u <= 1.0f))
                    u = 1.0f;
                if (!(0.0f <= u))
                    u = 0.0f;
                u2 = u * u;
                u3 = u * u2;
                one = 1.0f;
                L.b3 = u3 - u2;
                L.b2 = (u3 - (u2 + u2)) + u;
                L.b1 = -((u3 + u3) - u2 * 3.0f);
                L.b0 = ((u3 + u3) - u2 * 3.0f) + one;
                head = *(int *)(S + 0x604);
                cur = *(int *)(S + 0x608);
                j = (head - cur + 0x41) % 0x20;
                p1 = S + j * 0x30;
                p0 = S + idx * 0x30;
                SCALE(p1, out, L.b0);
                SCALE(p0, &L.tmp, L.b1);
                ADD3(out, &L.tmp, out);
                k = L.b2 * seg;
                SCALE(p1 + 0x20, &L.tmp, k);
                ADD3(out, &L.tmp, out);
                k = L.b3 * seg;
                SCALE(p0 + 0x20, &L.tmp, k);
                ADD3(out, &L.tmp, out);
                *(float *)(out + 0xC) = one;
                {
                    int ub;

                    __asm__("mfc1 %0, %1" : "=r"(ub) : "f"(u));
                    __asm__ __volatile__("qmtc2.ni %2, vf7\n"
                                         "lqc2 vf5, 0x0(%0)\n"
                                         "lqc2 vf6, 0x0(%1)\n"
                                         "vsubx.w vf8, vf0, vf7x\n"
                                         "vmulax.xyz ACC, vf5, vf7x\n"
                                         "vmaddw.xyz vf5, vf6, vf8w\n"
                                         "sqc2 vf5, 0x0(%3)\n"
                                         :
                                         : "r"(p0 + 0x10), "r"(p1 + 0x10), "r"(ub), "r"(tan)
                                         : "memory");
                }
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                     "vmul.xyz vf7, vf5, vf5\n"
                                     "vmulax.w ACC, vf0, vf7x\n"
                                     "vmadday.w ACC, vf0, vf7y\n"
                                     "vmaddz.w vf7, vf0, vf7z\n"
                                     "vrsqrt Q, vf0w, vf7w\n"
                                     "vwaitq\n"
                                     "vmulq.xyz vf5, vf5, Q\n"
                                     "sqc2 vf5, 0x0(%0)\n"
                                     :
                                     : "r"(tan)
                                     : "memory");
                return 1;
            }
            cur++;
            d += seg;
            *(int *)(S + 0x608) = cur;
        } while (cur < 0x1F);
    }
    return 0;
}
#endif
