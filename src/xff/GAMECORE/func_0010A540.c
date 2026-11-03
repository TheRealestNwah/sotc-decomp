typedef struct {
    char pad0[0x30];
    int f30;
    int f34;
    char pad38[0x2C];
    float f64;
    char pad68[0x20];
    float f88;
} Param;

typedef struct {
    char pad0[0xC4];
    int fC4;
    int fC8;
    Param *p;
    char padD0[0x60];
    float f130;
    float f134;
    char pad138[4];
    float f13C;
} Work;

static int func_0010A540(Work *w, int flag)
{
    Param *p = w->p;
    float r;

    if (p->f34 != 0) {
        if (w->fC4 != 0 && p->f64 * 0.5f < __builtin_fabsf(w->f130))
            return 0;
        if (w->fC8 != 0 && w->f13C / p->f88 < 1.0f && p->f64 * 0.5f < __builtin_fabsf(w->f134))
            return 0;
        if (flag == 0) {
            if (w->f13C / p->f88 < 1.0f && p->f64 * 0.5f < __builtin_fabsf(w->f134))
                return 0;
            return 1;
        }
        if (p->f30 == 0)
            return 1;
        r = w->f13C / p->f88;
        if (9.0f < w->f13C && __builtin_fabsf(w->f130) / p->f64 < r)
            return 1;
    }
    return 0;
}
