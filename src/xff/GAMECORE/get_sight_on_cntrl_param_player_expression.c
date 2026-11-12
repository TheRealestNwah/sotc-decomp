extern char *GetCharacterClass(int);
extern void func_00081FF0(int *, int);

#ifdef NONMATCHING /* 196 diffs, 196 vs 202 words: stack-arg store order and switch/branch layout (jump table RO_0017F5B0: cases 13 and 24 skip the body) */
void get_sight_on_cntrl_param_player_expression(int *p0, int *p1, int *p2, float *f3, float *f4, float *f5, float *f6,
                                                float *f7, float *p8, float *p9, int *p10, int *p11, int *p12,
                                                float *p13, float *p14, float *p15, float *p16, float *p17,
                                                float *p18, int obj)
{
    int sp[8] __attribute__((aligned(16)));
    char *chr = GetCharacterClass(obj);
    int s0;
    int s3;
    float z;

    if (*(char **)(chr + 0x578) == 0)
        s0 = 1;
    else
        s0 = (*(unsigned *)(*(char **)(chr + 0x578) + 0x6C) >> 10) & 0x1F;
    *p0 = 0;
    *p1 = 2;
    *p2 = 0;
    *f3 = 0.0f;
    z = *f3;
    *f5 = z;
    *f4 = z;
    *f7 = z;
    *p9 = z;
    *p8 = z;
    *p12 = 0;
    *p11 = 0;
    *p10 = 0;
    *p15 = z;
    *p14 = z;
    *p13 = z;
    *p16 = 89.0f;
    *p17 = -89.0f;
    *p18 = z;
    if (s0 < 13) {
        if (s0 >= 11)
            *p2 = 1;
    }
    s3 = s0 < 0x18;
    if (s3 && !(s0 < 13))
        *f3 = 0.5f;
    else
        *f3 = 0.3f;
    if (s0 < 0x1B && s0 >= 0x19) {
        *f4 = 10.0f;
        *f5 = -10.0f;
        *f6 = 80.0f;
        *f7 = -80.0f;
    }
    if (s0 == 13 || s0 == 2 || s0 == 0x18) {
        *p8 = 30.0f;
        *p9 = -30.0f;
    }
    switch (s0) {
    case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
    case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
    case 25: case 26:
        if ((unsigned)(s0 - 0x19) < 2) {
            *p0 = 1;
            *p1 = 0;
        } else {
            *p1 = 1;
        }
        func_00081FF0(sp, s0);
        *p10 = 1;
        *p13 = *(float *)&sp[1];
        if (sp[3] == 0)
            *p11 = 1;
        if (sp[5] == 0)
            *p12 = 1;
        *p16 = *(float *)&sp[2];
        *p14 = *(float *)&sp[2];
        *p17 = *(float *)&sp[4];
        *p15 = *(float *)&sp[4];
        *p16 = *p16 + 1.0f;
        *p17 = *p17 - 1.0f;
        break;
    case 13:
    case 24:
    default:
        break;
    }
    if (s0 < 0x1A && !s3)
        *p18 = -5.0f;
    else
        *p18 = 5.0f;
}
#endif
