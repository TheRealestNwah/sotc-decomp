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

extern void init_motion_ik_base(int *);
void begin_motion_ik_interest(char *m)
{
    if (*(int *)(m + 4) == 0) {
        constructor_motion_ik_base(m);
        *(int *)(m + 4) = 0;
        *(int *)(m + 8) = 0;
        *(int *)(m + 0xC) = 0;
        constructor_double_spring_interp_cntrl3D(m + 0x10, 0.0001f, 0.0f);
        *(s128 *)(m + 0x50) = ZeroVector;
        *(int *)(m + 0x60) = 0;
        *(s128 *)(m + 0x70) = ZeroVector;
        func_0003EEB0(m);
        init_motion_ik_base((int *)m);
        *(int *)(m + 4) = 1;
        *(int *)(m + 0xC) = 1;
    } else {
        *(int *)(m + 8) = 0;
    }
}
static void func_0003EEB0(char *p)
{
    *(int *)(p + 0x88) = 0;
    *(int *)(p + 0x84) = 0;
    *(int *)(p + 0x80) = 0;
}


