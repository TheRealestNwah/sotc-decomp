/* Finds a particle's collision hit by its configured mode and returns the hit position and plane. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern int D_001370D4;
extern int CollisionPlaneJudgeCallbackParticle();
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int (*)(), int, int, int (*)(), void *);
extern int GetCrossPositionPlaneLine(void *, void *, void *, void *);
extern void func_000C6A50(Vec4 *, Vec4 *, void *);
extern void func_000C2520(Vec4 *, Vec4 *, void *);

static inline float distSq(const void *a, const void *b)
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

static int func_000C2360(Vec4 *pos, Vec4 *plane, char *obj, void *from, void *to, char *cfg)
{
    char buf[0x50];
    int hit = 0;
    int mode = *(int *)(cfg + 0x104);

    if (mode == 1) {
        hit = ClipCollisionFinder(buf, from, to, obj + 0x170);
        if (hit == 1)
            func_000C6A50(pos, plane, buf);
    } else if (mode == 2) {
        float r = *(float *)(cfg + 0x124);
        if (*(int *)(obj + 0x188) == 1) {
            Vec4 cross;
            if (GetCrossPositionPlaneLine(&cross, obj + 0xB0, from, to) == 1 &&
                (r <= 0.0f || distSq(&cross, obj + 0xA0) <= r * r)) {
                pos->q = cross.q;
                plane->q = *(s128 *)(obj + 0xB0);
                plane->f[3] = 0.0f;
                if (*(void **)(obj + 0x18C)) {
                    func_000C2520(pos, plane, *(void **)(obj + 0x18C));
                    *(void **)(obj + 0x18C) = 0;
                }
                hit = 1;
            }
        }
    } else {
        char *w = buf;
        hit = ClipCollisionDirectCallBack(w, from, to, D_001370D4, 0, 0, 0, CollisionPlaneJudgeCallbackParticle, 0);
        if (hit == 1) {
            func_000C6A50(pos, plane, w);
            func_000C2520(pos, plane, *(void **)(obj + 0x18C));
        }
    }
    return hit;
}
