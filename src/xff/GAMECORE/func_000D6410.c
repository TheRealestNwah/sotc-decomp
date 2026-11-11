extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern float GAMEUTIL_increase_pitch_limit_clip(int, int, float, float, float, float);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern int begin_and_update_get_yaw_pitch_camera_target_visible_angle_manager(void *, void *, void *, void *, float, float);
extern void end_get_yaw_pitch_camera_target_visible_angle_manager(void *);
extern void GAMEUTIL_doit_status_manager(void *, int, int, float);
extern void func_000D6D18(void *, void *, void *);
extern void func_000D6E48(float *, float *, void *, void *, int, int, float, float);
extern void func_000D6F28(void *, void *, int, int, int, float, float, float);
extern float get_upper_limit_clip_default_pitch_camera_target_approach(void *, float);
extern int get_yaw_pitch_camera_target_lost_angle(void *, void *, void *, void *, float, float);
extern int is_must_reach_normal_default_angle(void *, int);

#ifdef NONMATCHING /* 6 diffs: scheduling only; the a0=0 setup and the second cfg load swap around the yaw store, and mov.s $f13 vs the arg4 copy before func_000D6F28 */
static void func_000D6410(char *c, char *m, int arg2, int arg3, int arg4, float fparg0)
{
    float dir[4];
    float ang[4] __attribute__((aligned(16)));
    register char *cfg __asm__("$3");
    int state = 0;
    float zero = 0.0f;
    float p;

    ang[2] = zero;
    ang[3] = zero;
    func_000D6D18(dir, c, m);
    GAMEUTIL_get_yaw_pitch_by_direction(&ang[0], &ang[1], dir);
    cfg = *(char **)m;
    if (*(int *)(cfg + 0xA8) == 1) {
        ang[1] = zero;
    }
    func_000D6E48(&ang[2], &ang[3], c, m, arg2, arg3, ang[0], ang[1]);
    {
    float y = GAMEUTIL_increase_yaw(0, ang[0], ang[2]);
    float k = 0.017453293f;
    *(float *)(c + 0x30) = y;
    cfg = *(char **)m;
    p = GAMEUTIL_increase_pitch_limit_clip(0, 0, ang[1], ang[3], *(float *)(cfg + 0xAC) * k, *(float *)(cfg + 0xB0) * k);
    }
    *(float *)(c + 0x34) = p;
    p = get_upper_limit_clip_default_pitch_camera_target_approach(m + 0x6A0, p);
    *(float *)(c + 0x34) = p;
    func_000D6F28(c, m, arg2, arg3, arg4, *(float *)(c + 0x30), p, fparg0);
    {
        int s0 = *(int *)(*(char **)m + 0xD0);
        if (s0 == 1) {
            void *yaw = c + 0x30;
            void *pitch = c + 0x34;
            if (get_yaw_pitch_camera_target_lost_angle(yaw, pitch, m + 0x660, m, *(float *)yaw, *(float *)pitch) == s0) {
                state = 2;
            } else if (*(int *)(c + 0x378) != s0) {
                int r = is_must_reach_normal_default_angle(m, arg2);
                if (r == s0) {
                    state = 3;
                    if (begin_and_update_get_yaw_pitch_camera_target_visible_angle_manager(yaw, pitch, c + 0x390, m, *(float *)yaw, *(float *)pitch) != r) {
                        state = 1;
                    }
                } else {
                    state = 1;
                }
            }
        } else {
            state = *(int *)(c + 0x378) != 1;
        }
    }
    if (state != 3) {
        end_get_yaw_pitch_camera_target_visible_angle_manager(c + 0x390);
    }
    GAMEUTIL_doit_status_manager(c, state, 0, fparg0);
}
#endif
