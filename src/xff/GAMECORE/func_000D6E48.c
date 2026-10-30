typedef union {
    char *p;
    float f;
} Word;

extern float CAM_get_interp_slope_pitch_ofst(char *, char *);
extern int CAM_is_need_obstacle_avoid_ofst(char *);

static void func_000D6E48(float *yaw, float *pitch, char *cam, char *ch, char *mgr)
{
    *yaw = *pitch = 0.0f;
    *pitch += CAM_get_interp_slope_pitch_ofst(cam + 0x90, ch);
    if (CAM_is_need_obstacle_avoid_ofst(mgr) == 1)
        *pitch += *(float *)(ch + 0x175C) * (*(float *)(*(char **)(mgr + 0x2C44) + 0xB0) * 0.0174532924f);
    *yaw += *(float *)(((Word *)ch)->p + 0xC8) * 0.0174532924f;
    *pitch += *(float *)(((Word *)ch)->p + 0xCC) * 0.0174532924f;
}
