extern void constructor_double_spring_interp_cntrl3D(char *, float, float);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);

void constructor_camera_final_update(char *c)
{
    *(int *)c = -1;
    c += 0x10;
    constructor_double_spring_interp_cntrl3D(c, 0.0001f, 0.0f);
    set_param_double_spring_interp_common(c, 6.0f, -1.0f, 3.0f, -1.0f);
}
