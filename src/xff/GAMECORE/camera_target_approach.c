#include "gamecore/camera_target_approach.h"

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
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
extern int GAMEUTIL_is_status_change_status_manager(void *);
extern void CAM_reset_aim_angle_rot(void *);
extern void CAM_set_interp_param_aim_rot_common(void *, float, float);
extern float CAM_doit_aim_angle_rot(void *, int, float, float, float, float, float, float, float, float, float);
static inline void vecSubXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}
static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
typedef float Vec4_act_approach_judge_ray_check_camera_target_approach[4] __attribute__((aligned(16)));
extern void GAMEUTIL_get_direction_by_yaw(float *, float);
extern int CAM_get_target_riding_obj(void *);
extern void CAM_act_ray_check_for_camera(void *, float *, float *, int, int, int);
extern void GAMEUTIL_doit_status_manager(int, int, int, float);
#define SUB3(out, a, b) __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n" "lqc2 vf6, 0x0(%2)\n" "vsub.xyz vf5, vf5, vf6\n" "sqc2 vf5, 0x0(%0)\n" : : "r"(out), "r"(a), "r"(b) : "memory")
static inline float dot3(Vec4 *a, Vec4 *b)
{
    register float d __asm__("$2");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(d) : "r"(a), "r"(b));
    return d;
}
extern void *GAMEUTIL_get_riding_horse_object(void *);

static void func_000DAC30(int arg0, char *arg1, int unused, int arg3, float fp);
static float func_000DAD60(void *cam, int mode);

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
            ((void (*)(ApproachWork *, char **, void *, void *, float))func_000DAC30)(w, cam, game, arg, rate);
            return;
        }
    }
    GAMEUTIL_reset_status_manager(w, 0);
    GAMEUTIL_constructor_position_filter(w->filter);
    w->yaw = 0;
    CAM_init_aim_angle_rot(w->aim, 1);
}

void constructor_camera_target_approach(char *p)
{
    GAMEUTIL_reset_status_manager(p, 0);
    GAMEUTIL_constructor_position_filter(p + 0x10);
    *(int *)(p + 0x40) = 0;
    CAM_init_aim_angle_rot(p + 0x44, 1);
}

float get_upper_limit_clip_default_pitch_camera_target_approach(int *status, float fparg0)
{
    float var_f20;

    var_f20 = fparg0;
    if ((((int (*)(int *))GAMEUTIL_get_cur_status_status_manager)(status) == 1) && (var_f20 > -1.4835298061370849609375f)) {
        var_f20 = -1.4835298061370849609375f;
    }
    return var_f20;
}

int is_cut_default_pitch_interp_camera_target_approach(int *arg0)
{
    int temp_v0;
    int var_v0;

    temp_v0 = ((int (*)(int *))GAMEUTIL_get_cur_status_status_manager)(arg0);
    if ((temp_v0 != 1) || (var_v0 = GAMEUTIL_is_status_change_status_manager(arg0), (var_v0 != temp_v0))) {
        var_v0 = 0;
    }
    return var_v0;
}

void reset_pitch_rot_cntrl_camera_target_approach(char *control)
{
    CAM_reset_aim_angle_rot(control + 0x44);
}

float act_pitch_rot_camera_target_approach(char *c, float pitch, float aim, float dt)
{
    int on = GAMEUTIL_get_cur_status_status_manager(c) == 1;

    CAM_set_interp_param_aim_rot_common(c + 0x44, 0.0f, 0.3f);
    return CAM_doit_aim_angle_rot(c + 0x44, on, pitch, aim, 0.0f, 0.0f, 100.0f, 1.0f, 40.0f, 0.8f, dt);
}

void act_approach_judge_ray_check_camera_target_approach(void *a0, float *pos, float *look, char *st, char *cam, int t1)
{
    Vec4_act_approach_judge_ray_check_camera_target_approach dir;
    Vec4_act_approach_judge_ray_check_camera_target_approach tmp;
    char *c = cam + 0x23C;
    float *base = (float *)(st + 0x10);
    float d;

    GAMEUTIL_get_direction_by_yaw(dir, *(float *)(st + 0x40));
    vecScale(dir, dir, -1.0f);
    vecSubXYZ(tmp, *(float **)(((char * (*)(int))GetLayoutClass)(CAM_get_target_obj(c)) + 0x134), base);
    d = vecDot(tmp, dir);
    vecScale(tmp, dir, d);
    vecAddXYZ(pos, base, tmp);
    pos[1] += 0.6f;
    vecScale(tmp, dir, ((float (*)(void *, int))func_000DAD60)(c, GAMEUTIL_get_cur_status_status_manager(st)));
    vecAddXYZ(look, pos, tmp);
    CAM_act_ray_check_for_camera(a0, pos, look, t1, 0, CAM_get_target_riding_obj(c));
}

int get_status_camera_target_approach(char *work)
{
    return ((int (*)(int *))GAMEUTIL_get_cur_status_status_manager)((int *)(work + 0));
}

static void func_000DAC30(int arg0, char *arg1, int unused, int arg3, float fp)
{
    Vec4 v0[3];
    Vec4 v30;
    Vec4 v40;
    Vec4 *pd2init;
    Vec4 d1;
    Vec4 d2;
    register int flag __asm__("$19") = 0;
    float z;

    pd2init = &d2;
    if (((int (*)(void *, void *, void *, int, char *, int))act_approach_judge_ray_check_camera_target_approach)(v0, &v30, &v40, arg0, arg1, arg3) == 0) {
        Vec4 *p = (Vec4 *)(arg1 + 0x60);
        register Vec4 *pd1 __asm__("$4");
        register Vec4 *pd2 __asm__("$3");

        if (((int (*)(int))GAMEUTIL_get_cur_status_status_manager)(arg0) == 1 || p->f[0x34 / 4] <= -0.6981317f ||
            (pd1 = &d1, ({ SUB3(pd1, p, &v30); }), pd2 = pd2init, ({ SUB3(pd2, p, &v40); }), z = 0.0f, d2.f[1] = z, d1.f[1] = z, dot3(pd1, pd2) <= z)) {
            flag = 1;
        }
    }
    GAMEUTIL_doit_status_manager(arg0, flag, 0, fp);
}

static float func_000DAD60(void *cam, int mode)
{
    float r = 1.0f;

    if (GAMEUTIL_get_riding_horse_object(((void * (*)(void))CAM_get_target_obj)()))
        r = 2.0f;
    if (mode == 1)
        r += 0.5f;
    return r;
}
