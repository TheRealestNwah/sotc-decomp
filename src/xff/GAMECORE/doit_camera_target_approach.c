typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    char filter[0x30];
    float yaw;
    char aim[1];
} ApproachWork;

extern int is_approach_rise_ok_camera_place_status(void *);
extern int is_reset_or_lws_movie_or_cutout_game_camera(void *);
extern int CAM_is_visible_now_target_visibility(void *);
extern void *CAM_get_target_obj(void *);
extern char *GetLayoutClass(void *);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern void GAMEUTIL_doit_position_filter(void *, Vec4 *, int);
extern float GAMEUTIL_get_object_move_noise(void *);
extern void GAMEUTIL_set_parameter_position_filter(void *, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern void GAMEUTIL_reset_status_manager(void *, int);
extern void GAMEUTIL_constructor_position_filter(void *);
extern void CAM_init_aim_angle_rot(void *, int);
extern void func_000DAC30(ApproachWork *, char **, void *, void *, float);

void doit_camera_target_approach(ApproachWork *w, char **cam, void *game, void *arg, float rate)
{
    int on = *(int *)(*cam + 0x118);

    if (on == 1) {
        int ok = is_approach_rise_ok_camera_place_status((char *)cam + 0x1270);

        if (ok == on && !is_reset_or_lws_movie_or_cutout_game_camera(game)
            && CAM_is_visible_now_target_visibility((char *)cam + 0x520) == ok) {
            char *place = (char *)cam + 0x60;
            void *obj = CAM_get_target_obj((char *)cam + 0x23C);
            Vec4 pos;

            pos.q = **(s128 **)(GetLayoutClass(obj) + 0x134);
            if (GAMEUTIL_get_cur_status_status_manager(w) == 0) {
                GAMEUTIL_doit_position_filter(w->filter, &pos, 1);
                w->yaw = *(float *)(place + 0x30);
            } else {
                GAMEUTIL_set_parameter_position_filter(w->filter, GAMEUTIL_get_object_move_noise(obj));
                GAMEUTIL_doit_position_filter(w->filter, &pos, 0);
                if (GAMEUTIL_get_difference_yaw_and_yaw(w->yaw, *(float *)(place + 0x30)) >= 0.052359879f)
                    w->yaw = *(float *)(place + 0x30);
            }
            func_000DAC30(w, cam, game, arg, rate);
            return;
        }
    }
    GAMEUTIL_reset_status_manager(w, 0);
    GAMEUTIL_constructor_position_filter(w->filter);
    w->yaw = 0;
    CAM_init_aim_angle_rot(w->aim, 1);
}
