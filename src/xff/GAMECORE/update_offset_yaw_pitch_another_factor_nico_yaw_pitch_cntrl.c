extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);

void update_offset_yaw_pitch_another_factor_nico_yaw_pitch_cntrl(void *arg0, float fparg0, float fparg1)
{
    (*(float *)((char *)(arg0) + 0x40)) = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2((*(float *)((char *)(arg0) + 0x5C)), fparg0);
    (*(float *)((char *)(arg0) + 0x50)) = GAMEUTIL_get_move_radi_from_pitch1_to_pitch2((*(float *)((char *)(arg0) + 0x68)), fparg1);
}
