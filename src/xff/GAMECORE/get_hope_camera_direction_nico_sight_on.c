extern void GAMEUTIL_get_direction_by_yaw_pitch(int, float, float);
extern float get_base_pitch_nico_yaw_pitch_cntrl(int);
extern float get_base_yaw_nico_yaw_pitch_cntrl(int);

void get_hope_camera_direction_nico_sight_on(int arg0, int arg1)
{
    float temp_f20;
    int temp_s0;

    temp_s0 = arg1 + 0xC;
    temp_f20 = get_base_yaw_nico_yaw_pitch_cntrl(temp_s0);
    GAMEUTIL_get_direction_by_yaw_pitch(arg0, temp_f20, get_base_pitch_nico_yaw_pitch_cntrl(temp_s0));
}
