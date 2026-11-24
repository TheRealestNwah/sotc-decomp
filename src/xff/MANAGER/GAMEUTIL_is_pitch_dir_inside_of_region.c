/* Tests whether a pitch direction lies inside the region between two bounding directions: splits the region into lo/hi vectors, projects dir and both bounds onto the y/z plane and checks the signs of three VU0 outer products. */
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Q4;
extern int GAMEUTIL_act_pitch_rot(Q4 *, Q4 *, int, float, float, float);
static inline void outer(V4 *dst, V4 *a, V4 *b)
{
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf05, vf06\n"
                         "vopmsub.xyz vf07, vf06, vf05\n"
                         "vsub.w vf07, vf07, vf07\n"
                         "sqc2 vf07, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

int GAMEUTIL_is_pitch_dir_inside_of_region(Q4 *out0, Q4 *out1, float *dir, Q4 *base, float range)
{
    Q4 lo, hi;
    float h = range * 0.5f;
    GAMEUTIL_act_pitch_rot(&lo, base, 0, h, 1.48352986f, -1.48352986f);
    GAMEUTIL_act_pitch_rot(&hi, base, 0, -h, 1.48352986f, -1.48352986f);
    if (out0 != 0) out0->q = lo.q;
    if (out1 != 0) out1->q = hi.q;
    {
        V4 a = (V4){dir[1], 0.0f, dir[2], 0.0f};
        V4 b = (V4){lo.f[1], 0.0f, lo.f[2], 0.0f};
        V4 c = (V4){hi.f[1], 0.0f, hi.f[2], 0.0f};
        V4 t[3];
        /* Pinned so the address setups land in the Original's registers. */
        register V4 *pa __asm__("$7") = &a;
        register V4 *pb __asm__("$4") = &b;
        register V4 *pc __asm__("$6") = &c;
        register V4 *pt __asm__("$5") = t;
        outer(pt, pb, pa);
        outer(&t[1], &b, &c);
        if (t[0].y * t[1].y > 0.0f) {
            outer(&t[2], &a, pc);
            if (t[1].y * t[2].y > 0.0f) return 1;
        }
    }
    return 0;
}
