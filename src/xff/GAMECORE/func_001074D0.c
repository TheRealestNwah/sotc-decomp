extern int chkEstimatCollisionCore(void *, int, void *, float, float, float);

static int func_001074D0(char *p, int arg, float a, float b)
{
    int id = *(int *)(*(char **)(p + 0x14) + 0x750);
    char *c = *(char **)(p + 0xCC);

    if (id != *(int *)(c + 0x8C) && id != *(int *)(c + 0x90))
        return 0;
    return chkEstimatCollisionCore(p, arg, p + 0x120, a, b, *(float *)(c + 0xCC));
}
