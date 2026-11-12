typedef int s128 __attribute__((mode(TI)));

extern int camera_collision_check_direct(void *, void *, void *, void *, int, int, void *, int);
extern int camera_collision_check_with_keep(void *, void *, void *, void *, void *, int);
extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern void update_by_cam_and_look_at_posi_mode_common_camera_data(void *);
extern void update_by_yaw_pitch_mode_common_camera_data(void *);
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(void *, float);
extern int is_acting_rewind_camera_dist_to_look_at(void *);
extern float GAMEUTIL_get_interp_yaw(float, float, float);
extern float GAMEUTIL_get_interp_pitch(float, float, float);

#ifdef NONMATCHING /* 109 diffs: frame layout (res 0x30, tmp 0x50), calls and branch structure match; argument registers pinned $s0..$s6 but the constant-1 register reuse ($s3), the prev pointer, and branch-likely delay-slot fills differ */
static inline float distSq(char *a, char *b)
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

void func_000DD3A8(s128 *out0, char *st0, char *co0, int a30, float dt, int move, char *pos0, char *cam0)
{
    register s128 *out __asm__("$17") = out0;
    register char *st __asm__("$16") = st0;
    register char *co __asm__("$18") = co0;
    register int a3 __asm__("$22") = a30;
    register char *pos __asm__("$20") = pos0;
    register char *cam __asm__("$21") = cam0;
    char res[0x30] __attribute__((aligned(16)));
    char tmp[0x50] __attribute__((aligned(16)));
    char *prev;
    float dpos;
    float dprev;
    int ok;
    register s128 v __asm__("$2");

    __asm__("" : "+r"(out), "+r"(st), "+r"(co));
    __asm__("" : "+r"(a3), "+r"(pos), "+r"(cam));
    if (move == 1) {
        if (*(int *)(st + 0x44) == 0) {
            prev = co + 0x60;
            dpos = distSq(st, pos);
            dprev = distSq(st, prev);
            if (dprev < dpos) {
                ok = camera_collision_check_direct(tmp, st, pos, cam, move, 0, *(void **)(co + 0x504), 1) == 0;
                if (ok != 0) {
                    v = *(s128 *)pos;
                } else {
                    ConvertFromCollisionPointToDynamics(res, tmp);
                    if (ok != 0)
                        v = *(s128 *)pos;
                    else
                        v = *(s128 *)prev;
                }
            } else {
                v = *(s128 *)pos;
            }
        } else {
            if (camera_collision_check_with_keep(res, co, out, pos, cam, 0) != 1)
                v = *(s128 *)pos;
            else
                v = *(s128 *)res;
        }
        *out = v;
        update_by_cam_and_look_at_posi_mode_common_camera_data(out);
        GAMEUTIL_reset_interp_ratio_cntrl(st + 0x110);
    } else if (a3 == 1 && is_acting_rewind_camera_dist_to_look_at(co + 0x11F0) == 0) {
        float r = GAMEUTIL_doit_interp_ratio_cntrl(st + 0x110, dt);
        if (r < 1.0f) {
            char *p = co + 0x60;
            *(s128 *)tmp = *out;
            *(float *)((char *)out + 0x30) = GAMEUTIL_get_interp_yaw(*(float *)(p + 0x30), *(float *)((char *)out + 0x30), r);
            *(float *)((char *)out + 0x34) = GAMEUTIL_get_interp_pitch(*(float *)(p + 0x34), *(float *)((char *)out + 0x34), r);
            update_by_yaw_pitch_mode_common_camera_data(out);
            if (camera_collision_check_with_keep(res, co, tmp, out, cam, 0) == a3) {
                *out = *(s128 *)res;
                update_by_cam_and_look_at_posi_mode_common_camera_data(out);
            }
        }
    } else {
        GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(st + 0x110, dt);
    }
}
#endif
