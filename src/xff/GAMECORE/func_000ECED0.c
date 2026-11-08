#ifdef NONMATCHING
/* Parked: 7 words differ (s3/s4 swap between the yaw pointer and c+0x44, and the yaw store timing). */
extern float D_0017B720;
extern void CAM_set_interp_param_aim_rot_common(void *, float, float);
extern float CAM_doit_aim_angle_rot(void *, int, float, float, float, float, float, float, float, float, float);

#define F(b, o) (*(float *)((char *)(b) + (o)))
#define I(b, o) (*(int *)((char *)(b) + (o)))

static void func_000ECED0(float *yaw, float *pitch, char *c, char *p, char *q)
{
    float a, b, e, d;

    if (I(c, 0x88) == 0) {
        a = F(p, 0x30);
        b = F(p, 0x34);
        e = F(p, 0x38);
        d = F(p, 0x3C);
    } else {
        a = F(p, 0x40);
        b = F(p, 0x44);
        e = F(p, 0x48);
        d = F(p, 0x4C);
    }
    CAM_set_interp_param_aim_rot_common(c, 0.0f, 0.8f);
    *yaw = CAM_doit_aim_angle_rot(c, I(p, 0x18), F(q, 0xD0), F(p, 0x10), F(p, 0x24), F(p, 0x28), a, b, e, d, D_0017B720);
    if (I(c, 0x88) == 0) {
        a = F(p, 0x5C);
        b = F(p, 0x60);
        e = F(p, 0x64);
        d = F(p, 0x68);
    } else {
        a = F(p, 0x6C);
        b = F(p, 0x70);
        e = F(p, 0x74);
        d = F(p, 0x78);
    }
    CAM_set_interp_param_aim_rot_common(c + 0x44, 0.0f, 0.8f);
    *pitch = CAM_doit_aim_angle_rot(c + 0x44, I(p, 0x1C), F(q, 0xD4), F(p, 0x14), F(p, 0x50), F(p, 0x54), a, b, e, d, D_0017B720);
}
#endif
