typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroVector;
extern void constructor_motion_ik_base(char *);
extern void constructor_double_spring_interp_cntrl3D(char *, float, float);
static void func_0003EEB0(char *);

void constructor_motion_ik_interest(char *m)
{
    float z = 0.0f;
    constructor_motion_ik_base(m);
    *(int *)(m + 4) = 0;
    *(int *)(m + 8) = 0;
    *(int *)(m + 0xC) = 0;
    constructor_double_spring_interp_cntrl3D(m + 0x10, 0.0001f, z);
    *(s128 *)(m + 0x50) = ZeroVector;
    *(float *)(m + 0x60) = z;
    *(s128 *)(m + 0x70) = ZeroVector;
    func_0003EEB0(m);
}
