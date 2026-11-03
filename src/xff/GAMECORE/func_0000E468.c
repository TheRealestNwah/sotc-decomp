/* NOTE: func_0000E0B8 is really (char *, float); declaring it (float, char *) gives the original f12-before-a0 arg order. Same registers. */
extern float func_0000E010(char *, float);
extern float func_0000E0B8(float, char *);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern float GAMEUTIL_increase_yaw_limit_clip(int, int, float, float, float, float);

static float func_0000E468(char *c, float yaw, float add, float base)
{
    float max, min;

    if (*(int *)(c + 0x104) == 1) {
        if (*(int *)(c + 0x108) == 1)
            max = func_0000E010(c, base);
        else
            max = GAMEUTIL_increase_yaw(0, *(float *)(c + 0x110), *(float *)(c + 0x128));
        if (*(int *)(c + 0x10C) == 1)
            min = func_0000E0B8(base, c);
        else
            min = GAMEUTIL_increase_yaw(0, *(float *)(c + 0x110), *(float *)(c + 0x12C));
        return GAMEUTIL_increase_yaw_limit_clip(0, 0, yaw, add, max, min);
    }
    return GAMEUTIL_increase_yaw(0, yaw, add);
}
