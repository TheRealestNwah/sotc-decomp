typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern int D_001370D4;
extern int CollisionPlaneJudgeCallbackParticle();
extern int ClipCollisionDirectCallBack(void *, Vec4 *, Vec4 *, int, int, int, int, void *, int);

static inline void scale(Vec4 *o, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(v), "r"(s) : "memory");
}

static inline void add(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b) : "memory");
}

int radiate_particle_collision_check_ray(void *c, Vec4 *out, char *p, float t)
{
    Vec4 d;
    scale(&d, (Vec4 *)(p + 0x30), t);
    add(out, (Vec4 *)(p + 0x10), &d);
    out->f[3] = 1.0f;
    return ClipCollisionDirectCallBack(c, (Vec4 *)(p + 0x10), out, D_001370D4, 0, 0, 0, CollisionPlaneJudgeCallbackParticle, 0);
}
