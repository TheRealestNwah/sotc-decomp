typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    char interp0[0x10];
    char interp1[0x10];
    float f30;
    float f34;
    float f38;
    float f3C;
    float f40;
    float f44;
    char pad48[0x50 - 0x48];
    Vec4 dir;
    char ratio[0x20];
    int n80;
    char pad84[0x90 - 0x84];
    char slope[0x350 - 0x90];
    float f350;
    float f354;
    char interp2[0x10];
    char interp3[0x10];
    char pad378[0x390 - 0x378];
    char visible[0x780 - 0x390];
    int n780;
    char pad784[0x790 - 0x784];
    Vec4 quat;
    Vec4 pos0;
    int n7B0;
    char pad7B4[0x7C0 - 0x7B4];
    Vec4 pos1;
    Vec4 pos2;
    Vec4 pos3;
} CameraDefaultAngle;

extern Vec4 ZUnitVector;
extern Vec4 IdentityQuaternion;
extern Vec4 ZeroPoint;
extern void GAMEUTIL_reset_status_manager(void *, int);
extern void constructor_aim_angle_interp_cntrl(void *, int);
extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern void CAM_reset_slope_cntrl(void *);
extern void func_000D6C60(void *);
extern void constructor_camera_target_visible_angle_manager(void *);

void constructor_camera_default_angle(CameraDefaultAngle *c)
{
    GAMEUTIL_reset_status_manager(c, 0);
    constructor_aim_angle_interp_cntrl(c->interp0, 1);
    constructor_aim_angle_interp_cntrl(c->interp1, 2);
    c->f30 = c->f34 = 0.0f;
    c->f38 = c->f3C = 0.0f;
    c->f40 = c->f44 = 0.0f;
    c->dir.q = ZUnitVector.q;
    GAMEUTIL_constructor_interp_ratio_cntrl(c->ratio);
    c->n80 = 0;
    CAM_reset_slope_cntrl(c->slope);
    c->f350 = c->f354 = 0.0f;
    constructor_aim_angle_interp_cntrl(c->interp2, 0);
    constructor_aim_angle_interp_cntrl(c->interp3, 2);
    func_000D6C60(c);
    constructor_camera_target_visible_angle_manager(c->visible);
    c->n780 = 0;
    c->quat.q = IdentityQuaternion.q;
    c->pos0.q = ZeroPoint.q;
    c->n7B0 = 0;
    c->pos1.q = ZeroPoint.q;
    c->pos2.q = ZeroPoint.q;
    c->pos3.q = ZeroPoint.q;
}
