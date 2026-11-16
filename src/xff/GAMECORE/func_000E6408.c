extern float D_0017B720;
extern void func_000ECBD8(char *, char *, void *);
extern void func_000ECC00(char *, char *, void *);
extern void func_000E65E8(char *, char *, void *);
extern void func_000E69E8(char *);
extern void doit_camera_target_lost_angle(void *, char *, char *, void *, float);
extern void doit_camera_target_approach(void *, char *, char *, void *, float);
extern void CAM_doit_base_look_at(void *, char *, char *, void *, float);
extern void doit_camera_dist_to_look_at(void *, char *, char *, void *, float);
extern void CAM_doit_look_at_spring(void *, char *, char *, void *, float);
extern void CAM_doit_obstacle_avoid_cntrl(void *, char *, char *, void *, float);
extern void doit_camera_default_angle(void *, char *, char *, void *, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);
extern void CAM_set_param_view_cut_avoid_cntrl(void *, float, float);
extern void CAM_reset_view_cut_avoid_cntrl(void *, int);
extern void CAM_doit_view_cut_avoid_cntrl(void *, char *, void *, float);

static void func_000E6408(char *cam, char *ctx, void *coll)
{
    char *vc = cam + 0x16B0;
    char *p;
    int m;

    func_000ECBD8(cam, ctx, coll);
    doit_camera_target_lost_angle(cam + 0x660, cam, ctx, coll, D_0017B720);
    doit_camera_target_approach(cam + 0x6A0, cam, ctx, coll, D_0017B720);
    CAM_doit_base_look_at(cam + 0xFC0, cam, ctx, coll, D_0017B720);
    doit_camera_dist_to_look_at(cam + 0x11F0, cam, ctx, coll, D_0017B720);
    CAM_doit_look_at_spring(cam + 0xF40, cam, ctx, coll, D_0017B720);
    CAM_doit_obstacle_avoid_cntrl(cam + 0x174C, cam, ctx, coll, D_0017B720);
    doit_camera_default_angle(cam + 0x730, cam, ctx, coll, D_0017B720);
    GAMEUTIL_get_direction_by_yaw_pitch(cam + 0xF20, *(float *)(cam + 0x770), *(float *)(cam + 0x774));
    *(float *)(cam + 0xF30) = *(float *)(cam + 0x770);
    *(float *)(cam + 0xF34) = *(float *)(cam + 0x774);
    *(int *)(cam + 0xF3C) = 0;
    *(int *)(cam + 0xF38) = 0;
    func_000ECC00(cam, ctx, coll);
    func_000E65E8(cam, ctx, coll);
    func_000E69E8(cam);
    p = *(char **)(ctx + 0x2C44);
    m = *(int *)(ctx + 0x1360);
    if (m < 7) {
        if (m > 0) {
            if (m == 1)
                CAM_set_param_view_cut_avoid_cntrl(vc, *(float *)(p + 0x70), *(float *)(p + 0x8C));
            else
                CAM_set_param_view_cut_avoid_cntrl(vc, 0.0f, 0.0f);
            CAM_doit_view_cut_avoid_cntrl(vc, cam, ctx + 0x2C44, D_0017B720);
            return;
        }
    }
    CAM_reset_view_cut_avoid_cntrl(vc, 0);
}
