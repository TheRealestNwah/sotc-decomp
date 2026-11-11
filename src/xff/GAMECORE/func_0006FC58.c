typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroVector;
extern int get_main_cameraman(void);
extern int get_game_camera(int);
extern int is_enable_base_yaw_rot_nico_yaw_pitch_cntrl(void *);
extern int is_enable_base_pitch_rot_nico_yaw_pitch_cntrl(void *);
extern int get_boss_interest_position_game_camera(void *, int);
extern void get_look_at_position_game_camera(void *, int);
extern int GAMEUTIL_check_and_get_normalize_vector(void *, int, void *);
extern int GAMEUTIL_get_yaw_pitch_by_direction(void *, void *, void *);
extern float GAMEUTIL_increase_yaw(int, float, float);

static void func_0006FC58(char *o, float f0, float f1)
{
    struct { s128 boss; s128 look; s128 dir; } v;
    char *s4 = o + 0xC;
    int cam;
    int a;
    int b;
    int c;
    int d;

    cam = get_game_camera(get_main_cameraman());
    a = is_enable_base_yaw_rot_nico_yaw_pitch_cntrl(s4);
    if (a == 1) {
        b = is_enable_base_pitch_rot_nico_yaw_pitch_cntrl(s4);
        if (b == a && f0 == 0.0f && f1 == 0.0f) {
            c = get_boss_interest_position_game_camera(&v.boss, cam);
            if (c == b) {
                get_look_at_position_game_camera(&v.look, cam);
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                     "lqc2 vf6, 0x0(%1)\n"
                                     "vsub.xyz vf5, vf5, vf6\n"
                                     "sqc2 vf5, 0x0(%2)\n"
                                     :
                                     : "r"(&v.boss), "r"(&v.look), "r"(&v.dir)
                                     : "memory");
                d = GAMEUTIL_check_and_get_normalize_vector(&v.dir, 0, &v.dir);
                if (d == c && GAMEUTIL_get_yaw_pitch_by_direction(o + 0x150, o + 0x154, &v.dir) == d) {
                    *(float *)(o + 0x150) = GAMEUTIL_increase_yaw(0, *(float *)(o + 0x150), -*(float *)(s4 + 0x7C));
                    *(int *)o = 2;
                    return;
                }
            }
        }
    }
    {
        s128 z = ZeroVector;

        *(int *)o = 1;
        *(s128 *)(o + 0x150) = z;
    }
}

