extern void func_00113118(char *p, float *q);

static void func_001130A8(char *p, float *q)
{
    char *c = *(char **)(p + 0xCC);
    unsigned int kind = *(int *)(c + 0xBC);

    if (kind - 2 < 2) {
        func_00113118(p, q);
        return;
    }
    if (kind == 1) {
        q[1] += *(float *)(c + 0xC0);
    } else if (kind - 4 < 2) {
        q[1] = *(float *)(c + 0xC0);
    }
}
