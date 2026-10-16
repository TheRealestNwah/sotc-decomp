typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint, ZUnitVector;
extern void constructor_double_spring_interp_cntrl(void *, float);
extern void reset_double_spring_interp_cntrl(void *, float);
extern void reset_time_interp_param_camera_dist_to_look_at(void *);

void constructor_camera_dist_to_look_at(char *c)
{
    char *p0;

    constructor_double_spring_interp_cntrl(c, 0.001f);
    reset_double_spring_interp_cntrl(c, 4.5f);
    *(float *)(c + 0x20) = 4.5f;
    p0 = c + 0x30;
    *(int *)(p0 + 0x0) = 0;
    *(float *)(p0 + 0x8) = 1.0f;
    *(int *)(p0 + 0x4) = 0;
    *(s128 *)(p0 + 0x10) = ZeroPoint;
    *(s128 *)(p0 + 0x20) = ZUnitVector;
    *(int *)(p0 + 0x30) = 0;
    reset_time_interp_param_camera_dist_to_look_at(c);
    *(int *)(c + 0x7C) = 0;
}
