extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);
extern float func_0000E3E8(float, float, float, void *);
extern int is_enable_base_pitch_rot_nico_yaw_pitch_cntrl(void *);

float update_base_pitch_nico_yaw_pitch_cntrl(void *arg0, float fparg0) {
    float temp_f0;
    float temp_f20;

    if (is_enable_base_pitch_rot_nico_yaw_pitch_cntrl(arg0) == 1) {
        temp_f20 = (*(float *)((char *)(arg0) + 0x68));
        temp_f0 = func_0000E3E8(temp_f20, fparg0, temp_f20, arg0);
        (*(float *)((char *)(arg0) + 0x68)) = temp_f0;
        return GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(temp_f20, temp_f0);
    }
    return 0.0f;
}
