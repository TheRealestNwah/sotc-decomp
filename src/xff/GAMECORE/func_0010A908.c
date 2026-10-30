extern int chkEstimatCollisionCore(void *, int, void *, float, float, float);

static int func_0010A908(char *p, int arg, float a, float b)
{
    return chkEstimatCollisionCore(p, arg, p + 0x120, a, b, *(float *)(*(char **)(p + 0xCC) + 0x68));
}
