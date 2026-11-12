/* Parked draft: camera rewind step. When the camera distance-to-look-at rewind is active and the
   normalised target direction is shorter than the rewind distance it pulls the camera position
   toward the target; then collision-checks the new position, converts the hit to dynamics and
   either copies it back (rewind finished) or ends the rewind. Returns whether it is still
   rewinding. Continues in func_000DD370 (epilogue). Written from the m2c draft. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern void CopyCollisionDynamics(int, void *);
extern int GAMEUTIL_check_and_get_normalize_vector(Vec4 *, float *, Vec4 *);
extern void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(int);
extern int camera_collision_check_direct(void *, int, void *, int);
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

static inline void scaleAdd(Vec4 *out, Vec4 *base, Vec4 *dir, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "qmtc2.ni %3, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(base), "r"(dir), "r"(s) : "memory");
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

static int func_000DD1C8(int arg0, Vec4 *from, int camera, Vec4 *target, int arg3, int t1)
{
    Vec4 dir __attribute__((aligned(16)));
    Vec4 dyn __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 hit __attribute__((aligned(16)));
    struct { float dist; int owner; } ctl;
    int rew = camera + 0x11F0;
    int still = 1;
    int moved = 0;
    float limit;

    ctl.owner = arg0;
    ctl.dist = 1.0f;
    limit = get_rewind_begin_dist_to_target_camera_dist_to_look_at(rew, 1.0f);
    if (is_acting_rewind_camera_dist_to_look_at(rew) == 1) {
        subXYZ(&dir, target, from);
        if (GAMEUTIL_check_and_get_normalize_vector(&dir, &ctl.dist, &dir) == 1 && ctl.dist < limit) {
            scaleAdd(&pos, from, &dir, limit);
            moved = 1;
        }
    }
    if (moved == 0) {
        pos = *from;
    }
    if (camera_collision_check_direct(&hit, arg3, &pos, t1) == 0) {
        ConvertFromCollisionPointToDynamics(&dyn, &hit);
        if (is_acting_rewind_camera_dist_to_look_at(rew) != 1 || distSq(from, &pos) < ctl.dist * ctl.dist) {
            still = 0;
            CopyCollisionDynamics(ctl.owner, &dyn);
        } else {
            end_rewind_camera_dist_to_look_at(rew, &dyn);
            GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(camera + 0x630);
        }
    }
    return still;
}
#endif
