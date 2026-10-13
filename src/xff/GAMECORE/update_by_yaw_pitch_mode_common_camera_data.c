extern void CAM_get_camera_position_by_look_at(void *, int, void *, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(int, float, float);

void update_by_yaw_pitch_mode_common_camera_data(void *arg0)
{
    int temp_s1;

    temp_s1 = arg0 + 0x20;
    GAMEUTIL_get_direction_by_yaw_pitch(temp_s1, (*(float *)((char *)(arg0) + 0x30)), (*(float *)((char *)(arg0) + 0x34)));
    CAM_get_camera_position_by_look_at(arg0, temp_s1, arg0 + 0x10, (*(float *)((char *)(arg0) + 0x38)));
}
