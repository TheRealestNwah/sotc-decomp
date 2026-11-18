typedef struct { float f[4]; } __attribute__((aligned(16))) V4;
static inline void vecNormalize(void *d, void *s)
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
                         : : "r"(d), "r"(s) : "memory");
}

static inline float vecDot(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
typedef int s128 __attribute__((mode(TI)));
extern char *CAM_get_target_obj(void *);
extern char *GAMEUTIL_get_parent_object(void *);
extern char *GetLayoutClass(void *);
extern V4 YUnitVector;
extern void create_original_view_matrix(void *, void *, void *, void *);
extern void iosApplyRotMatrix(void *, void *, void *);
extern float iosGetACosfExact(float);

static inline void quatDir(void *d, void *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(d), "r"(q) : "memory");
}

static float func_000E6B00(char **cam)
{
    float ang = 0.0f;

    if (*(int *)(*cam + 0x168)) {
        char *t = CAM_get_target_obj((char *)cam + 0x23C);
        char *lc;

        if (*(int *)(*cam + 0x16C) == 1)
            t = GAMEUTIL_get_parent_object(t);
        if (t != 0 && (lc = GetLayoutClass(t)) != 0) {
            V4 dir;
            V4 v;
            V4 q;
            float m[16] __attribute__((aligned(16)));

            *(s128 *)&q = *(s128 *)(lc + 0x80);
            quatDir(&dir, &q);
            create_original_view_matrix(m, (char *)cam + 0xE0, (char *)cam + 0x100, &YUnitVector);
            iosApplyRotMatrix(&v, m, &dir);
            if (v.f[2] < 0.999f) {
                v.f[2] = 0.0f;
                vecNormalize(&v, &v);
                ang = iosGetACosfExact(vecDot(&v, &YUnitVector));
                if (v.f[0] < 0.0f)
                    ang = -ang;
            }
        }
        ang = -ang;
    }
    return *(float *)(*cam + 0x170) * ang;
}

