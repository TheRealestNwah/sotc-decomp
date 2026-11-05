extern int D_001370D0;
extern int GetWaterSurfacePositionY(float *, char *, int, float, float);

static int func_000C5CC0(float *out, char *b, char *c, char *d)
{
    if (*(int *)(c + 0x15C) == 3 || *(int *)(c + 0x160) == 3 || *(int *)(d + 0xC8) == 1) {
        if (GetWaterSurfacePositionY(out, b + 0x10, D_001370D0, 100.0f, -500.0f) == 1)
            return 1;
    }
    *out = *(float *)(b + 0x14);
    return 0;
}
