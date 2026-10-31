extern void CAM_get_camera_space_axisXY(int, void *, void *, float);
extern float get_view_angle_camera_view_angle_cntrl(void *);
extern void set_camera_parameter_cameraman(void *, void *, void *, void *, float);

static void func_000EC148(void *cm, char *c)
{
    float v[4];

    CAM_get_camera_space_axisXY(0, v, c + 0x140, *(float *)(c + 0x1C4));
    set_camera_parameter_cameraman(cm, c + 0x120, c + 0x140, v, get_view_angle_camera_view_angle_cntrl(c + 0x1C8));
}
