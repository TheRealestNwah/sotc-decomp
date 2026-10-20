extern int GAMEUTIL_is_inside_of_region_yaw(float *, float *, float, float, float);
extern int GAMEUTIL_is_inside_of_region_pitch(float *, float *, float, float, float);
int CAM_is_inside_of_region_aim_angle_rot(float *first, float *second, int *mode,
                                        float value, float center, float width)
{
    if (*mode == 0)
        return GAMEUTIL_is_inside_of_region_yaw(first, second, value, center, width);
    return GAMEUTIL_is_inside_of_region_pitch(first, second, value, center, width);
}
