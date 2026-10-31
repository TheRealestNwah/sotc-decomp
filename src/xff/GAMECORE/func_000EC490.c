typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;
extern s128 ZeroVector;
extern void CAM_init_aim_angle_rot(void *, int);
extern void constructor_double_spring_interp_cntrl3D(void *, float, float);

static void func_000EC490(void *unused, char *c)
{
    char *a = c + 0x10;
    char *s = c + 0x90;

    *(int *)a = 0;
    *(s128 *)(a + 0x10) = ZeroPoint;
    constructor_double_spring_interp_cntrl3D(c + 0x30, 0.001f, 1.0f);
    *(int *)(a + 0x60) = 0;
    *(s128 *)(a + 0x70) = ZeroVector;
    CAM_init_aim_angle_rot(s, 0);
    CAM_init_aim_angle_rot(c + 0xD4, 1);
    *(int *)(s + 0x88) = 0;
    *(int *)(s + 0x8C) = 0;
    *(int *)(c + 0x120) = 0;
    *(int *)(c + 0x124) = 0;
    *(int *)(c + 0x128) = 0;
}
