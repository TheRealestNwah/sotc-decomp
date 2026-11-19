extern float D_0017B720;
extern int func_000EBD08(void *);
extern void func_000EBD48(char *, void *);
extern void GAMEUTIL_get_1p_right_analog_input(float *, float *);
extern int func_000E4EC0(char *, void *);
extern void *get_cur_camera_target(void *);
extern void CAM_doit_target(char *, void *, char *, char *, void *, float);
extern void CAM_doit_objective_target_visibility(char *, char *, char *, char *, void *);
extern void func_000EBD88(char *, char *);
extern void doit_camera_place_status(char *, char *, void *, float);
extern void func_000EBDF8(char *, char *, void *);
extern void func_000E5D58(char *, void *);
extern void func_000EBE88(char *, char *, void *);
extern int func_000EBEA0(char *, char *, void *);
extern void func_000E6408(char *, char *, void *);
extern int func_000E6070(char *, void *);
extern int func_000EBEF0(char *);
extern void func_000EBF58(char *, char *, int);
extern void doit_camera_view_angle_cntrl(char *, char *, int, float);
extern void func_000EC040(char *, char *, int);
extern void doit_camera_final_update(char *, char *, char *, void *, float);
extern void func_000EC148(void *, char *);
extern int act_camera_cutout_game_camera_param_manager(char *, char *);
extern void SetCameraResetSw(int);
extern void func_000E6CA0(char *, char *, void *);
extern void GAMEUTIL_constructor_col_plane_info(void *);

static void func_000E4C48(char *g, void *arg)
{
    char *cm = g + 0x1370;
    int r = func_000EBD08(arg);
    int flag;
    int mode;
    char *p;

    if (r == 1) {
        *(int *)(g + 4) = r;
        func_000EBD48(g, arg);
        GAMEUTIL_get_1p_right_analog_input((float *)(g + 0x137C), (float *)(g + 0x1380));
        *(int *)(g + 0x1360) = func_000E4EC0(g, arg);
        CAM_doit_target(g + 0x15AC, get_cur_camera_target(arg), cm, g, arg, D_0017B720);
        CAM_doit_objective_target_visibility(g + 0x1890, g + 0x13D0, cm, g, arg);
        func_000EBD88(cm, g);
        doit_camera_place_status(g + 0x25E0, g, arg, D_0017B720);
        func_000EBDF8(cm, g, arg);
        func_000E5D58(g, arg);
        if (*(int *)(g + 0x1360) == 7)
            func_000EBE88(g + 0x3270, cm, arg);
        else if (*(int *)(g + 0x1360) == 8)
            func_000EBEA0(g + 0x34E0, cm, arg);
        func_000E6408(cm, g, arg);
        func_000E6070(g, arg);
        flag = func_000EBEF0(g);
        func_000EBF58(cm, g, flag);
        doit_camera_view_angle_cntrl(cm + 0x1C8, g, flag, D_0017B720);
        func_000EC040(cm, g, flag);
        doit_camera_final_update(cm + 0x1760, cm, g, arg, D_0017B720);
        func_000EC148(arg, cm);
        mode = *(int *)(g + 0x1360);
        if (mode == 7)
            p = g + 0x3270;
        else if (mode == 8)
            p = g + 0x34E0;
        else
            p = 0;
        if (*(int *)(cm + 0x1838) == 1 || mode == 0 || (p != 0 && *(int *)(p + 0x98) == 1)
            || act_camera_cutout_game_camera_param_manager(g + 0x50, g) == 1)
            SetCameraResetSw(1);
        else
            SetCameraResetSw(0);
        func_000E6CA0(cm, g, arg);
    } else {
        GAMEUTIL_constructor_col_plane_info(g + 0x27B0);
        func_000EC148(arg, cm);
    }
    *(int *)(g + 0x1364) = *(int *)(g + 0x1360);
}
