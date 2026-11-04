extern char *D_001370D8;

static float func_000C6688(float x)
{
    float r = 1.0f;
    int i;

    if (x != 1.0f) {
        for (i = 0; i < *(int *)(D_001370D8 + 0xC); i++)
            r *= x;
    }
    return r;
}
