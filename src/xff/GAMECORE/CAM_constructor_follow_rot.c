typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint;
extern s128 ZeroVector;
extern void GAMEUTIL_constructor_interp_ratio_cntrl(char *);
extern void GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(char *, int);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(char *, float, float);
extern void GAMEUTIL_reset_interp_value_cntrl(char *, float);
extern void constructor_double_spring_interp_cntrl3D(char *, float, float);

void CAM_constructor_follow_rot(char *c)
{
    GAMEUTIL_constructor_interp_ratio_cntrl(c);
    GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(c, 1);
    GAMEUTIL_set_param_interp_ratio_cntrl(c, 0.0f, 0.5f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x20);
    GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(c + 0x20, 1);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x40);
    GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(c + 0x40, 1);
    GAMEUTIL_set_param_interp_ratio_cntrl(c + 0x40, 0.0f, 0.5f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x60);
    GAMEUTIL_reset_interp_value_cntrl(c + 0x80, 0.0f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x8C);
    GAMEUTIL_reset_interp_value_cntrl(c + 0xAC, 0.0f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0xB8);
    GAMEUTIL_reset_interp_value_cntrl(c + 0xD8, 0.0f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0xE4);
    GAMEUTIL_reset_interp_value_cntrl(c + 0x104, 0.0f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x110);
    GAMEUTIL_reset_interp_value_cntrl(c + 0x130, 0.0f);
    GAMEUTIL_constructor_interp_ratio_cntrl(c + 0x13C);
    GAMEUTIL_reset_interp_value_cntrl(c + 0x15C, 0.0f);
    *(s128 *)(c + 0x170) = ZeroPoint;
    *(s128 *)(c + 0x180) = ZeroPoint;
    *(s128 *)(c + 0x190) = ZeroPoint;
    *(float *)(c + 0x1A0) = 0.0f;
    *(float *)(c + 0x1A4) = 0.0f;
    *(float *)(c + 0x1A8) = 0.0f;
    *(float *)(c + 0x1AC) = 0.0f;
    *(float *)(c + 0x1B0) = 0.0f;
    *(float *)(c + 0x1B4) = 0.0f;
    *(float *)(c + 0x1B8) = 0.0f;
    constructor_double_spring_interp_cntrl3D(c + 0x1C0, 0.001f, 0.0f);
    *(s128 *)(c + 0x200) = ZeroVector;
}
