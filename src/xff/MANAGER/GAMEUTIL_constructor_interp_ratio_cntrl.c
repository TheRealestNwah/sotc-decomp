typedef struct { int a; int b; int c; float f; int d; } InterpRatio;
extern void GAMEUTIL_set_param_interp_ratio_cntrl(InterpRatio *, float, float);

void GAMEUTIL_constructor_interp_ratio_cntrl(InterpRatio *p)
{
    p->f = 0.0f;
    p->a = 1;
    p->c = 1;
    p->b = 0;
    p->d = 0;
    GAMEUTIL_set_param_interp_ratio_cntrl(p, p->f, 1.0f);
}
