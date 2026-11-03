typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;
extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern void constructor_nico_yaw_pitch_cntrl(char *);
extern void constructor_double_spring_interp_cntrl3D(char *, float, float);
extern void constructor_double_spring_interp_cntrl(char *, float);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
extern void set_rot_radi_value_flag_double_spring_interp_cntrl3D(char *, int, int, int);

#define I(o) (*(int *)(w + (o)))
#define F(o) (*(float *)(w + (o)))
#define Q(o) (*(s128 *)(w + (o)))

void constructor_nico_sight_on(char *w)
{
    I(0x0) = 0;
    I(0x4) = 0;
    I(0x8) = 0;
    constructor_nico_yaw_pitch_cntrl(w + 0xC);
    I(0x14C) = 0;
    Q(0x150) = ZeroVector;
    constructor_double_spring_interp_cntrl3D(w + 0x160, 0.0001f, 0.0f);
    set_param_double_spring_interp_common(w + 0x160, 9.0f, 3.1415926f, 4.5f, -1.0f);
    set_rot_radi_value_flag_double_spring_interp_cntrl3D(w + 0x160, 1, 0, 0);
    I(0x1A0) = 0;
    I(0x1A4) = 0;
    Q(0x1B0) = ZeroPoint;
    Q(0x1C0) = ZeroPoint;
    Q(0x1D0) = ZeroPoint;
    I(0x1E0) = 0;
    Q(0x1F0) = ZUnitVector;
    F(0x208) = 0.0f;
    F(0x204) = 0.0f;
    F(0x200) = 0.0f;
    constructor_double_spring_interp_cntrl(w + 0x20C, 0.0001f);
    set_param_double_spring_interp_common(w + 0x20C, 9.0f, -1.0f, 4.5f, -1.0f);
    constructor_double_spring_interp_cntrl(w + 0x22C, 0.0001f);
    set_param_double_spring_interp_common(w + 0x22C, 12.0f, -1.0f, 6.0f, -1.0f);
    constructor_double_spring_interp_cntrl3D(w + 0x250, 0.0001f, 0.0f);
    set_param_double_spring_interp_common(w + 0x250, 12.0f, -1.0f, 6.0f, -1.0f);
    set_rot_radi_value_flag_double_spring_interp_cntrl3D(w + 0x250, 1, 0, 0);
    I(0x290) = 0;
    F(0x29C) = 0.0f;
    F(0x2A4) = 0.0f;
    F(0x2A0) = 0.0f;
    F(0x2AC) = 0.0f;
    F(0x2A8) = 0.0f;
    F(0x2B4) = 0.0f;
    F(0x2B0) = 0.0f;
    F(0x2D4) = 0.0f;
    F(0x2D0) = 0.0f;
    F(0x2CC) = 0.0f;
    F(0x2C8) = 0.0f;
    F(0x2C4) = 0.0f;
    I(0x298) = 0;
    I(0x2C0) = 0;
    I(0x2BC) = 0;
    I(0x2B8) = 0;
    I(0x294) = 0;
}
