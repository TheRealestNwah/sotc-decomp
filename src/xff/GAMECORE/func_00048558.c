/* Parked: 148 diffs, same size (156 words; Original continues into the split tail func_000487A8). Ribbon strip builder: transforms each path point by the camera matrix (iosCopyMatrix of the camera context at +0x1A0, VU0 matrix multiply run), derives the tangent between consecutive transformed points (the last point extrapolates from the previous one), normalises it, crosses with ZUnitVector to a side vector scaled by point.w * 0.5, and writes two vertices (point +/- side) per point into the output with the depth in the 4th word. Locals in one struct (cur +0, a +0x10, b +0x20, c +0x30, dir +0x40, side +0x50, matrix +0x60, d +0xA0). Remaining: the Original keeps ten hoisted pointers in t1..t9/a-regs and fills delay slots differently; ours reloads addresses. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern Vec ZUnitVector;
extern char *iosgluGetCameraContext(void);
extern void iosCopyMatrix(void *, char *);

#define VADD(a, b, d)                                   \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "lqc2 vf6, 0x0(%1)\n"          \
                         "vadd.xyz vf5, vf5, vf6\n"     \
                         "sqc2 vf5, 0x0(%2)\n"          \
                         :                              \
                         : "r"(a), "r"(b), "r"(d)       \
                         : "memory")

#define VSUB(a, b, d)                                   \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "lqc2 vf6, 0x0(%1)\n"          \
                         "vsub.xyz vf5, vf5, vf6\n"     \
                         "sqc2 vf5, 0x0(%2)\n"          \
                         :                              \
                         : "r"(a), "r"(b), "r"(d)       \
                         : "memory")

#define XFORM(v, m, d)                                          \
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"                  \
                         "lqc2 vf14, 0x0(%1)\n"                 \
                         "lqc2 vf15, 0x10(%1)\n"                \
                         "lqc2 vf16, 0x20(%1)\n"                \
                         "lqc2 vf17, 0x30(%1)\n"                \
                         "vmulax.xyzw ACC, vf14, vf8x\n"        \
                         "vmadday.xyzw ACC, vf15, vf8y\n"       \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"       \
                         "vmaddw.xyzw vf10, vf17, vf8w\n"       \
                         "sqc2 vf10, 0x0(%2)\n"                 \
                         :                                      \
                         : "r"(v), "r"(m), "r"(d)               \
                         : "memory")

void func_00048558(char *o, char *out)
{
    struct {
        Vec cur;
        Vec a;
        Vec b;
        Vec c;
        Vec dir;
        Vec side;
        Vec m[4];
        Vec d;
    } L __attribute__((aligned(16)));
    char *pts;
    int count;
    int i;
    int j;
    int s0;
    int t8;
    float f1;
    float f2;
    float sc;
    int bits;
    char *p;
    char *a2;
    float *a3;

    pts = *(char **)(o + 0x70);
    count = *(int *)(o + 0x84);
    iosCopyMatrix(L.m, iosgluGetCameraContext() + 0x1A0);
    L.cur.q = *(s128 *)pts;
    L.cur.w = 1.0f;
    XFORM(&L.cur, &L.m[0], &L.a);
    f2 = L.a.z;
    L.a.z = 0.0f;
    i = 0;
    if (count > 0) {
        s0 = 0;
        t8 = 0;
        p = pts;
        do {
            if (i == count - 1) {
                VSUB(p, p - 0x10, &L.d);
                VADD(p, &L.d, &L.cur);
                L.cur.w = 1.0f;
            } else {
                L.cur.q = *(s128 *)(p + 0x10);
                L.cur.w = 1.0f;
            }
            XFORM(&L.cur, &L.m[0], &L.c);
            f1 = L.c.z;
            L.c.z = 0.0f;
            VSUB(&L.a, &L.c, &L.dir);
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
                                 : "r"(&L.dir)
                                 : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vopmula.xyz ACC, vf5, vf6\n"
                                 "vopmsub.xyz vf7, vf6, vf5\n"
                                 "vsub.w vf7, vf7, vf7\n"
                                 "sqc2 vf7, 0x0(%2)\n"
                                 :
                                 : "r"(&ZUnitVector), "r"(&L.dir), "r"(&L.side)
                                 : "memory");
            sc = *(float *)(p + 0xC) * 0.5f;
            __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(sc));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyzw vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 :
                                 : "r"(&L.side), "r"(bits)
                                 : "memory");
            a2 = out + ((s0 + i) << 4);
            a3 = (float *)(a2 + 8);
            for (j = 0; j < 2; j++) {
                if (j == 0) {
                    VADD(&L.a, &L.side, out + (t8 << 4));
                } else {
                    VSUB(&L.a, &L.side, a2);
                }
                *a3 = f2;
                a2 += 0x10;
                a3 += 4;
            }
            L.b.q = L.a.q;
            i++;
            L.a.q = L.c.q;
            f2 = f1;
            L.b.z = 0.0f;
            t8 += 3;
            s0 += 2;
            p += 0x10;
        } while (i < count);
    }
}
#endif
