#ifdef NONMATCHING /* 3 diffs (int return on CAM_get_warp_position, obj+0x10 passed directly, both found by permuter): scheduling only. The original moves the two float args into f12/f13 before computing w+0x1814 into t3; ours computes t3 first. */
typedef float Vec[4] __attribute__((aligned(16)));
extern int GAMEUTIL_is_boss_obj(int, int);
extern void CAM_add_plane_offset_in_position(float *, float *, float *, float);
extern int CAM_get_target_riding_obj(void *);
extern int CAM_get_warp_position(float *, float *, float *, float *, int, int, int, void *, float, float, int);

static inline float sqrtf_(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static int func_000D5CF0(char *obj, char *w, float *base, int a3, int t0, float dist, float f13, float f14)
{
    Vec pos;
    Vec d;
    float len2;
    float off;

    if (GAMEUTIL_is_boss_obj(*(int *)(obj + 0x30), 1) == 1)
        off = f14;
    else
        off = f13;
    CAM_add_plane_offset_in_position(pos, (float *)(obj + 0x10), (float *)(obj + 0x20), -off * 1.001f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(pos), "r"(base), "r"(d) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len2) : "r"(d) : "$2");
    if (dist * dist < len2) {
        float s = dist / sqrtf_(len2);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(d), "r"(s) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(base), "r"(d), "r"(pos) : "memory");
    }
    {
                CAM_get_warp_position((float *)(obj + 0x10), (float *)(obj + 0x10), pos, base, a3, t0, CAM_get_target_riding_obj(w + 0x23C), w + 0x1814, f13, f14, 1);
        { int *nv = (int *)(obj + 8); *nv = 1; }
        *(int *)(obj + 0xC) = 1;
    }
    return 1;
}
#endif
