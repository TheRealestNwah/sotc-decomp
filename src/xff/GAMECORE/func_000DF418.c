static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline float vecDot(float *a, float *b)
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
typedef float Vec4[4] __attribute__((aligned(16)));

extern float ZeroVector[];
extern void GAMEUTIL_get_local_directionX(float *, void *);
extern void GAMEUTIL_get_local_directionY(float *, void *);
extern void GAMEUTIL_get_local_directionZ(float *, void *);
extern float func_000E2670(void *, void *, float);
extern void GAMEUTIL_get_offset_position_by_option_space(void *, float *, float *, int, float *, float *, float *);

static void func_000DF418(void *out, float *pos, float *base, char *lim, void *mtx)
{
    Vec4 d;
    Vec4 dx;
    Vec4 dy;
    Vec4 dz;
    Vec4 loc;

    GAMEUTIL_get_local_directionX(dx, mtx);
    GAMEUTIL_get_local_directionY(dy, mtx);
    GAMEUTIL_get_local_directionZ(dz, mtx);
    vecSubXYZ(d, pos, base);
    loc[0] = vecDot(d, dx);
    loc[1] = vecDot(d, dy);
    loc[2] = vecDot(d, dz);
    loc[3] = 0.0f;
    loc[0] = func_000E2670(lim + 0x80, lim + 0xAC, loc[0]);
    loc[1] = func_000E2670(lim + 0xD8, lim + 0x104, loc[1]);
    loc[2] = func_000E2670(lim + 0x130, lim + 0x15C, loc[2]);
    GAMEUTIL_get_offset_position_by_option_space(out, ZeroVector, loc, 1, dx, dy, dz);
}
