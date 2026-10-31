typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float v[4]; } V4;

extern int act_camera_cutout_game_camera_param_manager(void *, void *);
extern int is_camera_target_debug_move(void *);
extern float get_mode_common_data_filter_base_dist_to_look_at(void *);
extern void CAM_get_camera_position_by_look_at(float *, float *, float *, float);

static inline int is_m(int m)
{
    if (m == 0 || m == 8)
        return 1;
    return 0;
}

static void func_000ECC00(char *o, char *c, void *t)
{
    char *s;
    int m = *(int *)(c + 0x1360);
    int a;
    int b;
    float f;

    a = is_m(m);
    if (a == 1 || act_camera_cutout_game_camera_param_manager(c + 0x50, c) == 1)
        b = 1;
    else
        b = 0;
    if (b != 1)
        return;
    s = o + 0xA0;
    *(qword *)(s + 0x10) = *(qword *)(o + 0xFD0);
    if (!is_camera_target_debug_move(t)) {
        ((V4 *)(s + 0x20))->q = ((V4 *)(o + 0xF20))->q;
        *(float *)(s + 0x30) = *(float *)(o + 0xF30);
        *(float *)(s + 0x34) = *(float *)(o + 0xF34);
    }
    f = get_mode_common_data_filter_base_dist_to_look_at(o);
    *(float *)(s + 0x38) = f;
    CAM_get_camera_position_by_look_at((float *)s, (float *)(o + 0xC0), (float *)(o + 0xB0), f);
}
