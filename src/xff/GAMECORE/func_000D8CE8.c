extern float RO_00180F98[];
extern float RO_00181010[];
extern float func_000D8DC0(float *, int, unsigned int *);

static float func_000D8CE8(unsigned int *s)
{
    switch (*s) {
    case 0:
        break;
    case 1:
        return func_000D8DC0(RO_00180F98, 7, s);
    case 2:
        return func_000D8DC0(RO_00181010, 6, s);
    }
    return 0.0f;
}
