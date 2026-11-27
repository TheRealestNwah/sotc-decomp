/* Parked: 58 words off. Camera rewind step: while the distance-to-look-at rewind is active and the
   target direction (t0 - a3) normalises to less than the rewind distance, the probe position is
   pulled to from + dir * limit (scale then add, through a temporary), else it is the target. Then
   collision-checks it, converts the hit to dynamics and either copies it back or ends the rewind.
   Returns whether it is still rewinding. Continues in func_000DD370 (epilogue). Left: the Original
   holds `still` in $s5 and camera+0x23C in $s7 (ours swaps them), rematerialises the hit buffer
   address instead of keeping it in $s2, and has one more word (a nop before the copy block). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern void CopyCollisionDynamics(int, void *);
extern int GAMEUTIL_check_and_get_normalize_vector(Vec4 *, float *, Vec4 *);
extern void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(int);
extern int camera_collision_check_direct(void *, void *, void *, int, int, int, int, int);
extern void end_rewind_camera_dist_to_look_at(int, void *);
extern float get_rewind_begin_dist_to_target_camera_dist_to_look_at(int, float);
extern int is_acting_rewind_camera_dist_to_look_at(int);

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scale3(void *out, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(s) : "memory");
}

static inline void add3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distSq(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

static int func_000DD1C8(int owner, int a1, char *camera, Vec4 *from, Vec4 *target, int t1)
{
    Vec4 pos __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    Vec4 tmp __attribute__((aligned(16)));
    Vec4 dyn[3] __attribute__((aligned(16)));
    Vec4 hit[5] __attribute__((aligned(16)));
    struct { float dist; int owner; } ctl;
    char *rew = camera + 0x11F0;
    int still = 1;
    int moved = 0;
    char *sub = camera + 0x23C;
    int none;
    float limit;

    ctl.owner = owner;
    ctl.dist = 1.0f;
    limit = get_rewind_begin_dist_to_target_camera_dist_to_look_at((int)rew, 1.0f);
    if (is_acting_rewind_camera_dist_to_look_at((int)rew) == 1) {
        subXYZ(&dir, target, from);
        if (GAMEUTIL_check_and_get_normalize_vector(&dir, &ctl.dist, &dir) == 1 && ctl.dist < limit) {
            scale3(&tmp, &dir, limit);
            add3(&pos, from, &tmp);
            moved = 1;
        }
    }
    if (moved == 0)
        pos.q = target->q;
    none = camera_collision_check_direct(hit, from, &pos, t1, 0, 0, *(int *)(sub + 0x2C8), 1) == 0;
    if (!none)
        ConvertFromCollisionPointToDynamics(dyn, hit);
    __asm__("" : "+r"(none));
    if (!none) {
        if (is_acting_rewind_camera_dist_to_look_at((int)rew) == 1 && !(distSq(from, dyn) < ctl.dist * ctl.dist)) {
            end_rewind_camera_dist_to_look_at((int)rew, dyn);
            GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl((int)(camera + 0x630));
        } else {
            CopyCollisionDynamics(ctl.owner, dyn);
            still = 0;
        }
    }
    return still;
}
#endif
