typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroVector;
extern void CAM_init_aim_angle_rot(void *, int);
extern void constructor_double_spring_interp_cntrl3D(void *, float, float);
extern void set_rot_radi_value_flag_double_spring_interp_cntrl3D(void *, int, int, int);

static void func_000EBA50(char *c)
{
    char *a = c + 4;
    char *s = c + 0xA0;

    *(int *)c = 0;
    CAM_init_aim_angle_rot(a, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    *(int *)(a + 0x88) = 0;
    *(float *)(a + 0x8C) = 0.0f;
    constructor_double_spring_interp_cntrl3D(s, 0.0001f, *(float *)(a + 0x8C));
    set_rot_radi_value_flag_double_spring_interp_cntrl3D(s, 1, 0, 0);
    *(s128 *)(c + 0xE0) = ZeroVector;
}
