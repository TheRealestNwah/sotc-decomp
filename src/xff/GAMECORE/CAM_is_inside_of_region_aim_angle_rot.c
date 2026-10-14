extern int GAMEUTIL_is_inside_of_region_yaw();
extern int GAMEUTIL_is_inside_of_region_pitch();

int CAM_is_inside_of_region_aim_angle_rot(int a, int b, int *c, int d)
{
    if (*c == 0) {
        return GAMEUTIL_is_inside_of_region_yaw(a, b, c, d);
    }
    return GAMEUTIL_is_inside_of_region_pitch(a, b, c, d);
}
