typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct {
    char pad0[0x60];
    Vec4 v60;
    Vec4 v70;
    Vec4 v80;
    char spring90[0x20];
    int b0;
    char padB4[0xC];
    Vec4 c0;
    char lookD0[0x54];
    char aim124[0x10];
    char aim134[0x10];
    int i144;
    char pad148[0x8];
    Vec4 v150;
    char spring160[0x10];
} TargetOffset;

extern Vec4 ZeroVector;
extern Vec4 ZeroPoint;
extern void constructor_double_spring_interp_cntrl3D(void *, float, float);
extern void constructor_double_spring_interp_cntrl(void *, float);
extern void set_param_double_spring_interp_common(void *, float, float, float, float);
extern void reset_double_spring_interp_cntrl(void *, float);
extern void GAMEUTIL_constructor_look_at_vs_offset(void *);
extern void constructor_aim_angle_interp_cntrl(void *, int);
extern void func_000E1970(TargetOffset *);

void CAM_reset_target_offset(TargetOffset *p)
{
    constructor_double_spring_interp_cntrl3D(p, 0.001f, 0.0f);
    constructor_double_spring_interp_cntrl((char *)p + 0x40, 0.001f);
    p->v60.q = ZeroVector.q;
    p->v70.q = ZeroVector.q;
    p->v80.q = ZeroVector.q;
    constructor_double_spring_interp_cntrl(p->spring90, 0.0001f);
    set_param_double_spring_interp_common(p->spring90, 10.0f, -1.0f, 5.0f, -1.0f);
    reset_double_spring_interp_cntrl(p->spring90, 1.0f);
    p->b0 = 0;
    p->c0.q = ZeroPoint.q;
    GAMEUTIL_constructor_look_at_vs_offset(p->lookD0);
    constructor_aim_angle_interp_cntrl(p->aim124, 0);
    constructor_aim_angle_interp_cntrl(p->aim134, 2);
    p->i144 = 0;
    p->v150.q = ZeroPoint.q;
    constructor_double_spring_interp_cntrl(p->spring160, 0.0001f);
    set_param_double_spring_interp_common(p->spring160, 10.0f, -1.0f, 5.0f, -1.0f);
    func_000E1970(p);
}
