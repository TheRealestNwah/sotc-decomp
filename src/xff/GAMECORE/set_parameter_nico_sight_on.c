extern float GAMEUTIL_increase_yaw(int, float, float);
extern void set_yaw_pitch_input_border_parameter_nico_yaw_pitch_cntrl(char *, float, float, float, float);
extern void set_offset_yaw_parameter_nico_yaw_pitch_cntrl(char *, float, float, float, float, float, float, float, float, float);
extern void set_base_yaw_parameter_nico_yaw_pitch_cntrl(char *, int, float, float, float, float, float, float);
extern void set_offset_pitch_parameter_nico_yaw_pitch_cntrl(char *, float, float, float, float, float, float, float, float, float);
extern void set_base_pitch_parameter_nico_yaw_pitch_cntrl(char *, int, float, float, float, float, float, float);
extern void set_max_min_pitch_parameter_nico_yaw_pitch_cntrl(char *, float, float);

void set_parameter_nico_sight_on(char *p, int i290, int i294, int i298, int i2B8, int i2BC, int i2C0,
                                 float f29C, float a2A0, float a2A4, float a2A8, float a2AC, float a2B0, float a2B4,
                                 float a2C4, float y0, float y1, float y2, float y3, float bd1, float bd3, float oy0,
                                 float oy1, float oy2, float oy3, float oy4, float oy5, float oy6, float oy7,
                                 float oy8, int byMode, float by0, float by1, float by2, float by3, float by4,
                                 float by5, float op1, float op2, float op3, float op4, float op5, float op6,
                                 float op7, float op8, int bpMode, float bp0, float bp1, float bp2, float bp3,
                                 float bp4, float bp5)
{
    char *c;

    *(int *)(p + 0x290) = i290;
    *(int *)(p + 0x294) = i294;
    *(int *)(p + 0x298) = i298;
    *(int *)(p + 0x2B8) = i2B8;
    *(int *)(p + 0x2BC) = i2BC;
    *(int *)(p + 0x2C0) = i2C0;
    *(float *)(p + 0x2A0) = a2A0 * 0.017453292519943295f;
    *(float *)(p + 0x2AC) = a2AC * 0.017453292519943295f;
    *(float *)(p + 0x2B0) = a2B0 * 0.017453292519943295f;
    *(float *)(p + 0x2B4) = a2B4 * 0.017453292519943295f;
    *(float *)(p + 0x2C4) = a2C4 * 0.017453292519943295f;
    *(float *)(p + 0x2A4) = a2A4 * 0.017453292519943295f;
    *(float *)(p + 0x2A8) = a2A8 * 0.017453292519943295f;
    *(float *)(p + 0x29C) = f29C;
    *(float *)(p + 0x2C8) = GAMEUTIL_increase_yaw(0, *(float *)(p + 0x2C4), y0 * 0.017453292519943295f);
    *(float *)(p + 0x2CC) = GAMEUTIL_increase_yaw(0, *(float *)(p + 0x2C4), y1 * 0.017453292519943295f);
    *(float *)(p + 0x2D0) = GAMEUTIL_increase_yaw(0, *(float *)(p + 0x2C4), y2 * 0.017453292519943295f);
    *(float *)(p + 0x2D4) = GAMEUTIL_increase_yaw(0, *(float *)(p + 0x2C4), y3 * 0.017453292519943295f);
    c = p + 0xC;
    set_yaw_pitch_input_border_parameter_nico_yaw_pitch_cntrl(c, 0.0f, bd1, 0.0f, bd3);
    set_offset_yaw_parameter_nico_yaw_pitch_cntrl(c, oy0, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8);
    if (*(int *)(p + 0x290) == 0)
        set_base_yaw_parameter_nico_yaw_pitch_cntrl(c, byMode, by0, by1, by2, by3, by4, by5);
    else
        set_base_yaw_parameter_nico_yaw_pitch_cntrl(c, byMode, 0.0f, 0.0f, 0.0f, 0.0f, by4, by5);
    set_offset_pitch_parameter_nico_yaw_pitch_cntrl(c, 0.0f, op1, op2, op3, op4, op5, op6, op7, op8);
    set_base_pitch_parameter_nico_yaw_pitch_cntrl(c, bpMode, bp0, bp1, bp2, bp3, bp4, bp5);
    set_max_min_pitch_parameter_nico_yaw_pitch_cntrl(c, 80.0f, -80.0f);
}
