extern void constructor_double_spring_interp_cntrl(char *, float);
extern void reset_double_spring_interp_cntrl(char *, float);

void constructor_camera_view_angle_cntrl(char *c)
{
    char *s = c + 0x20;
    constructor_double_spring_interp_cntrl(c, 0.001f);
    reset_double_spring_interp_cntrl(c, 45.0f);
    constructor_double_spring_interp_cntrl(s, 0.0001f);
    reset_double_spring_interp_cntrl(s, 1.0f);
}
