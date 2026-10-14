extern int GAMEUTIL_is_diff_nearly_equal_zero(float, float, float);
extern int is_leave_camera_dist_to_look_at(void **);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void CAM_get_camera_position_by_look_at(void *, void *, void *, float);
extern void T_000D7260(void *, void **, int, int, float);
extern void doit_double_spring_interp_cntrl(signed char *, int, float, float);
extern float func_000D78F8(signed char *, void **, int, float);
extern int is_reset_or_lws_movie_or_cutout_game_camera(int);

void doit_camera_dist_to_look_at(signed char *arg0, void **arg1, int arg2, int arg3, float fparg0) {
    float temp_f0;
    float var_f0;
    void *temp_s3;
    void *temp_v0;

    temp_s3 = (char *)arg1 + 0xA0;
    (*(float *)((char *)(arg0) + 0x1C)) = (float) (*(float *)((char *)(temp_s3) + 0x38));
    (*(float *)((char *)(arg0) + 0x20)) = func_000D78F8(arg0, arg1, arg2, fparg0);
    T_000D7260(arg0 + 0x30, arg1, arg2, arg3, fparg0);
    if (is_leave_camera_dist_to_look_at(arg1) == 1) {
        var_f0 = (*(float *)((char *)(temp_s3) + 0x38));
        goto block_4;
    }
    if ((*(int *)((char *)(arg0) + 0x30)) == 2) {
        var_f0 = 0.1f;
block_4:
        (*(float *)((char *)(arg0) + 0x20)) = var_f0;
    }
    temp_v0 = *arg1;
    set_param_double_spring_interp_common(arg0, (*(float *)((char *)(temp_v0) + 0x144)), (*(float *)((char *)(temp_v0) + 0x14C)), (*(float *)((char *)(temp_v0) + 0x148)), -1.0f);
    doit_double_spring_interp_cntrl(arg0, is_reset_or_lws_movie_or_cutout_game_camera(arg2), (*(float *)((char *)(arg0) + 0x20)), fparg0);
    if (GAMEUTIL_is_diff_nearly_equal_zero((*(float *)((char *)(temp_s3) + 0x38)), (*(float *)((char *)(arg0) + 0x1C)), 0.001f) == 0) {
        temp_f0 = (*(float *)((char *)(arg0) + 0x1C));
        (*(float *)((char *)(temp_s3) + 0x38)) = temp_f0;
        CAM_get_camera_position_by_look_at(temp_s3, temp_s3 + 0x20, temp_s3 + 0x10, temp_f0);
    }
}
