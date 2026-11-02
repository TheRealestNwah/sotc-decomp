typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    char aim10[0x10];
    char aim20[0x10];
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    char pad48[8];
    Vec4 unk50;
    char interp60[0x20];
    int unk80;
    char pad84[0xC];
    char slope90[0x2C0];
    float unk350;
    float unk354;
    char aim358[0x10];
    char aim368[0x28];
    char visible390[0x3F0];
    int unk780;
    char pad784[0xC];
    Vec4 unk790;
    Vec4 unk7A0;
    int unk7B0;
    char pad7B4[0xC];
    Vec4 unk7C0;
    Vec4 unk7D0;
    Vec4 unk7E0;
} CameraDefaultAngle;

extern Vec4 IdentityQuaternion;
extern Vec4 ZUnitVector;
extern Vec4 ZeroPoint;
extern void GAMEUTIL_reset_status_manager(void *, int);
extern void constructor_aim_angle_interp_cntrl(void *, int);
extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern void CAM_reset_slope_cntrl(void *);
extern void func_000D6C60(void *);
extern void constructor_camera_target_visible_angle_manager(void *);

void constructor_camera_default_angle(CameraDefaultAngle *angle)
{
    GAMEUTIL_reset_status_manager(angle, 0);
    constructor_aim_angle_interp_cntrl(angle->aim10, 1);
    constructor_aim_angle_interp_cntrl(angle->aim20, 2);
    angle->unk30 = angle->unk34 = 0.0f;
    angle->unk38 = angle->unk3C = 0.0f;
    angle->unk40 = angle->unk44 = 0.0f;
    angle->unk50.q = ZUnitVector.q;
    GAMEUTIL_constructor_interp_ratio_cntrl(angle->interp60);
    angle->unk80 = 0;
    CAM_reset_slope_cntrl(angle->slope90);
    angle->unk350 = angle->unk354 = 0.0f;
    constructor_aim_angle_interp_cntrl(angle->aim358, 0);
    constructor_aim_angle_interp_cntrl(angle->aim368, 2);
    func_000D6C60(angle);
    constructor_camera_target_visible_angle_manager(angle->visible390);
    angle->unk780 = 0;
    angle->unk790.q = IdentityQuaternion.q;
    angle->unk7A0.q = ZeroPoint.q;
    angle->unk7B0 = 0;
    angle->unk7C0.q = ZeroPoint.q;
    angle->unk7D0.q = ZeroPoint.q;
    angle->unk7E0.q = ZeroPoint.q;
}
