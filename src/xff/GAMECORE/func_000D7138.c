/* Updates the camera's target-visibility status from a ray check at the look-at camera position. */
#ifdef NONMATCHING
/* Parked attempt: 4 differing words, the order of the argument moves around
 * the CAM_act_ray_check_for_camera and GAMEUTIL_doit_status_manager calls.
 * Pinning the saved registers fixes the $s5-$s7 allocation (was 7 diffs). */
typedef float Vec4[4] __attribute__((aligned(16)));

extern void GAMEUTIL_reset_status_manager(char *, int);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);
extern void CAM_get_camera_position_by_look_at(void *, void *, void *, float);
extern void *CAM_get_target_riding_obj(void *);
extern int CAM_act_ray_check_for_camera(void *, void *, void *, void *, int, void *);
extern void GAMEUTIL_doit_status_manager(char *, int, int, float);
extern float GAMEUTIL_get_status_continue_time_status_manager(char *);
extern int GAMEUTIL_get_cur_status_status_manager(char *);

static void func_000D7138(char *cam_, char *a_, void *c, int mode, float rate)
{
    Vec4 dir;
    register char *a __asm__("$16") = a_;
    register char *cam __asm__("$17") = cam_;
    register char *sm __asm__("$18") = cam + 0x37C;
    register char *look __asm__("$19") = a + 0x60;
    register char *ride __asm__("$20") = a + 0x23C;
    register char *pos __asm__("$22") = cam + 0x7E0;
    register char *ray __asm__("$23") = a + 0x520;

    if (mode == 1) {
        *(int *)(cam + 0x378) = mode;
        GAMEUTIL_reset_status_manager(sm, 1);
        return;
    }
    GAMEUTIL_get_direction_by_yaw_pitch(dir, *(float *)(cam + 0x364), *(float *)(cam + 0x374));
    CAM_get_camera_position_by_look_at(pos, dir, a + 0x70, *(float *)(look + 0x38));
    GAMEUTIL_doit_status_manager(sm, CAM_act_ray_check_for_camera(0, ray, pos, c, 0, CAM_get_target_riding_obj(ride)), 0, rate);
    if (GAMEUTIL_get_status_continue_time_status_manager(sm) >= 1.0f)
        *(int *)(cam + 0x378) = GAMEUTIL_get_cur_status_status_manager(sm);
}
#endif
