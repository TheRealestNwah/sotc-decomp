/* Parked: 106 diffs, same size (156 words; Original continues into the split tail func_000456A0, which finishes the GetQuaternionFromMatrix call). Spawn orientation for a path actor: copies the source quad into the actor, picks a geometry position + surface plane (n % count) or, with no geometry, a random circle offset and a random unit direction; builds a right/up/forward frame with three VU0 normalise runs and two vopmula/vopmsub cross products, and calls GetQuaternionFromMatrix with the matrix in a stack struct (rows +0x50, +0x60, +0x70 copied to +0x10..+0x30, zero row +0x40; direction and ZeroPoint passed as 128-bit by-value args in a2/a3). Remaining: n is kept in s0 by the Original (ours a3), the s6 alias of &pos, and prologue/store order. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint;
extern void *memset(void *, int, unsigned int);
extern void AI_GetRandomCircleOfsXZ(float *, float, float);
extern float iosGetRandom(void);
extern void GetGeometryPointerPosition(char *, char *, int);
extern s128 *GetGeometryPointerSurfacePlane(char *);
extern void GetQuaternionFromMatrix(char *, s128 *, s128, s128);

#define NORM(p)                                         \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "vmul.xyz vf7, vf5, vf5\n"     \
                         "vmulax.w ACC, vf0, vf7x\n"    \
                         "vmadday.w ACC, vf0, vf7y\n"   \
                         "vmaddz.w vf7, vf0, vf7z\n"    \
                         "vrsqrt Q, vf0w, vf7w\n"       \
                         "vwaitq\n"                     \
                         "vmulq.xyz vf5, vf5, Q\n"      \
                         "sqc2 vf5, 0x0(%0)\n"          \
                         :                              \
                         : "r"(p)                       \
                         : "memory")

#define CROSS(a, b, d)                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "lqc2 vf6, 0x0(%1)\n"          \
                         "vopmula.xyz ACC, vf5, vf6\n"  \
                         "vopmsub.xyz vf7, vf6, vf5\n"  \
                         "vsub.w vf7, vf7, vf7\n"       \
                         "sqc2 vf7, 0x0(%2)\n"          \
                         :                              \
                         : "r"(a), "r"(b), "r"(d)       \
                         : "memory")

void func_00045458(char *o, char *src, int n)
{
    struct {
        float v[4];
        s128 m[4];
        s128 c;
        s128 plane;
        s128 dir;
    } L __attribute__((aligned(16)));
    char *s2 = o + 0xC0;
    char *s4 = o + 0xB0;
    char *s5 = o + 0xD0;
    char *s6 = s4;
    int cnt;
    int off;
    float one;

    *(int *)(o + 0x8C) = 1;
    *(s128 *)(o + 0xE0) = *(s128 *)src;
    *(s128 *)(o + 0xD0) = *(s128 *)src;
    *(int *)(o + 0x98) = 0;
    *(float *)(o + 0xE4) = *(float *)(o + 0xE4) + 10.0f;
    *(int *)(o + 0x9C) = 0;
    *(int *)(o + 0x94) = 0;
    *(int *)(o + 0x90) = 0;
    *(int *)(o + 0x88) = 0;
    cnt = *(int *)(src + 0x20);
    if (cnt > 0) {
        off = (n % cnt) << 6;
        GetGeometryPointerPosition(s4, *(char **)(src + 0x24) + off, 0x10);
        *(s128 *)(o + 0xC0) = *GetGeometryPointerSurfacePlane(*(char **)(src + 0x24) + off);
    } else {
        memset(L.v, 0, 0x10);
        L.v[0] = -10.0f;
        AI_GetRandomCircleOfsXZ(L.v, 10.0f, 15.0f);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(s5), "r"(L.v), "r"(s6)
                             : "memory");
        one = 1.0f;
        *(float *)s2 = 2.0f * iosGetRandom() - one;
        *(float *)(s2 + 4) = 2.0f * iosGetRandom() - one;
        *(int *)(s2 + 0xC) = 0;
        *(float *)(s2 + 8) = 2.0f * iosGetRandom() - one;
        NORM(s2);
    }
    L.plane = *(s128 *)s2;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(s4), "r"(o + 0xE0), "r"(&L.dir)
                         : "memory");
    NORM(&L.dir);
    CROSS(&L.plane, &L.dir, &L.c);
    NORM(&L.c);
    CROSS(&L.c, &L.plane, &L.dir);
    *(int *)((char *)&L.c + 0xC) = 0;
    *(int *)((char *)&L.plane + 0xC) = 0;
    *(int *)((char *)&L.dir + 0xC) = 0;
    L.m[0] = L.c;
    L.m[1] = L.plane;
    L.m[2] = L.dir;
    L.m[3] = ZeroPoint;
    GetQuaternionFromMatrix(o + 0xA0, L.m, L.dir, ZeroPoint);
}
#endif
