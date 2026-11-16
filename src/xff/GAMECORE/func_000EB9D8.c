typedef int s128 __attribute__((mode(TI)));
extern s128 ZUnitVector;
extern void CAM_init_aim_angle_rot(void *, int);

static void func_000EB9D8(char *c)
{
    char *a = c + 4;

    *(int *)c = 0;
    CAM_init_aim_angle_rot(a, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    *(int *)(a + 0x88) = 0;
    *(int *)(a + 0x8C) = 0;
    *(int *)(c + 0x94) = 0;
    *(int *)(c + 0x98) = 0;
    *(s128 *)(c + 0xA0) = ZUnitVector;
    *(float *)(c + 0xB0) = *(float *)(c + 0xB4) = 0.0f;
}
