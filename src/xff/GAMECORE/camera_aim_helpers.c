typedef struct {
    int target;
    int a;
    int b;
    float c;
    int d;
    float max;
    float min;
    int e;
    int f;
    char interp[1];
} AimRot;
extern void GAMEUTIL_reset_interp_ratio_cntrl(int *);
static void func_000E1650(void *);
static float func_000E15F8(float value, float limit)
{
    if (limit <= value)
        return 1.0f;
    return value / limit;
}
static void func_000E1620(AimRot *object)
{
    func_000E1650(object);
    object->f = 0;
    GAMEUTIL_reset_interp_ratio_cntrl((int *)object->interp);
}
static void func_000E1650(void *object)
{
    *(int *)((char *)object + 4) = 0;
}
