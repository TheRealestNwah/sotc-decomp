extern float RO_00180F68[];
extern float RO_00180FD0[];
extern float func_000D8DC0(float *, int, unsigned int *);

static float func_000D8C70(unsigned int *s)
{
    switch (*s) {
    case 0:
        break;
    case 1:
        return func_000D8DC0(RO_00180F68, 6, s);
    case 2:
        return func_000D8DC0(RO_00180FD0, 8, s);
    }
    return 0.0f;
}
