/* Parked: 121 diffs, same size (132 words; Original tail is the split func_00037C58). Slide/sweep probe: offsets the start and end points by dir * step0 (VU0), then up to 10 times probes with ClipCollisionDirectCallBack (flag set) or ClipCollisionFinderCallBack against character_ikcolattrfilter; on a hit lerps the midpoint (0.5), nudges by dir * step1 and retries; copies the clipped point (or *a2 when the budget runs out) to *out. Locals in one struct: t +0x10, s +0x20, e +0x30, hit +0x40 (0x40 bytes, hit point at +0x80), m +0x90, d +0xA0, n +0xB0; the Original spills a2/flag/count to sp+0xC0/0xC4/0xC8 and keeps out in fp, finder in s2, dir in s3 (pins don't change the count). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern int character_ikcolattrfilter(void *, void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
extern int ClipCollisionFinderCallBack(void *, void *, void *, void *, void *, int);

void func_00037A38(Vec *outp, Vec *a1, Vec *a2, Vec *dirp, int flag, void *finderp, float step0, float step1)
{
    register Vec *out __asm__("$30") = outp;
    register Vec *dir __asm__("$19") = dirp;
    register void *finder __asm__("$18") = finderp;
    struct {
        Vec t;
        Vec s;
        Vec e;
        char hit[0x40];
        Vec hp;
        Vec m;
        Vec d;
        Vec n;
    } L __attribute__((aligned(16)));
    int count;
    int r;

    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(dir), "r"(*(int *)&step0), "r"(&L.t)
                         : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(a1), "r"(&L.t), "r"(&L.s)
                         : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(a2), "r"(&L.t), "r"(&L.e)
                         : "memory");
    count = 10;
again:
    if (flag != 0)
        r = ClipCollisionDirectCallBack(L.hit, &L.s, &L.e, finder, 0, 0, 0, character_ikcolattrfilter, 0);
    else
        r = ClipCollisionFinderCallBack(L.hit, &L.s, &L.e, finder, character_ikcolattrfilter, 0);
    if (r == 0) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(&L.e), "r"(&L.t), "r"(out)
                             : "memory");
        return;
    }
    {
        float half = 0.5f;

        __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyz ACC, vf5, vf7x\n"
                             "vmaddw.xyz vf5, vf6, vf8w\n"
                             "sqc2 vf5, 0x0(%3)\n"
                             :
                             : "r"(*(int *)&half), "r"(&L.s), "r"(&L.e), "r"(&L.m)
                             : "memory");
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(dir), "r"(*(int *)&step1), "r"(&L.d)
                         : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(&L.m), "r"(&L.d), "r"(&L.n)
                         : "memory");
    count--;
    if (count != 0) {
        if (flag != 0)
            r = ClipCollisionDirectCallBack(L.hit, &L.n, &L.m, finder, 0, 0, 0, character_ikcolattrfilter, 0);
        else
            r = ClipCollisionFinderCallBack(L.hit, &L.n, &L.m, finder, character_ikcolattrfilter, 0);
        if (r != 0) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 :
                                 : "r"(&L.hp), "r"(&L.t), "r"(&L.e)
                                 : "memory");
            goto again;
        }
    }
    out->q = a2->q;
}
#endif
