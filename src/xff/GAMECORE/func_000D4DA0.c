typedef struct {
    float f[4];
} __attribute__((aligned(16))) Vec4;

typedef int s128 __attribute__((mode(TI)));

extern float func_000D5FD0(Vec4 *, Vec4 *, int);
extern float func_000D5FF0(Vec4 *, Vec4 *, Vec4 *, int);
extern float func_000D6020(Vec4 *, Vec4 *, int);
extern int func_000D6040(float);
extern void GAMEUTIL_get_answer_of_2jihouteishiki(float *, float *, float, float, float);

static inline float distSq(Vec4 *a, Vec4 *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void lerpXYZ(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static int func_000D4DA0(Vec4 *out, Vec4 *a, Vec4 *b, Vec4 *c, float r)
{
    int hit = 0;
    float r2;
    float a0, a1, a2, b0, b1, b2, c0, c1, c2;
    float ans[2];
    float t;

    r -= 0.01f;
    r2 = 0.0f;
    if (r < r2) {
        r = r2;
    }
    r2 = r * r;
    if (r2 <= distSq(c, a)) {
        *(s128 *)out = *(s128 *)a;
    } else if (distSq(c, b) <= r2) {
        *(s128 *)out = *(s128 *)b;
        hit = 1;
    } else {
        t = -1.0f;
        a0 = func_000D5FD0(a, b, 0);
        b0 = func_000D5FF0(a, b, c, 0);
        c0 = func_000D6020(b, c, 0);
        a1 = func_000D5FD0(a, b, 1);
        b1 = func_000D5FF0(a, b, c, 1);
        c1 = func_000D6020(b, c, 1);
        a2 = func_000D5FD0(a, b, 2);
        b2 = func_000D5FF0(a, b, c, 2);
        c2 = func_000D6020(b, c, 2);
        GAMEUTIL_get_answer_of_2jihouteishiki(&ans[0], &ans[1], a0 + a1 + a2, b0 + b1 + b2, c0 + c1 + c2 - r2);
        if (func_000D6040(ans[0])) {
            t = ans[0];
        } else if (func_000D6040(ans[1])) {
            t = ans[1];
        }
        if (func_000D6040(t) == 1) {
            lerpXYZ(out, a, b, t);
            hit = 1;
        } else {
            *(s128 *)out = *(s128 *)a;
        }
    }
    return hit;
}
