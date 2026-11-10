typedef int s128 __attribute__((mode(TI)));
typedef struct { float f0; float f4; float f8; } Param3;
extern float D_001798B0;
extern void doit_double_spring_interp_cntrl3D(int, void *, int, int, float);
extern void reset_double_spring_interp_cntrl3D(int, s128 *, int, int);
extern void set_param_double_spring_interp_common(int, float, float, float, float);

#ifdef NONMATCHING /* 16 diffs: the constant 1 is materialized twice (original shares $a3 with the reset call), arg0 pinned to $s1 by search */
static void func_000ED110(char *p0, Param3 *arg1, int arg2, s128 *arg3)
{
    register char *arg0 __asm__("$17") = p0;
    int base = (int)(arg0 + 0x20);

    set_param_double_spring_interp_common(base, arg1->f0, arg1->f8, arg1->f4, -1.0f);
    if (*(int *)arg0 == 0) {
        if (arg2 != 1) {
            return;
        }
        *(int *)arg0 = arg2;
        *(s128 *)(arg0 + 0x10) = *arg3;
        reset_double_spring_interp_cntrl3D(base, arg3, 0, 1);
        return;
    }
    if (arg2 == 1) {
        *(s128 *)(arg0 + 0x10) = *arg3;
    }
    doit_double_spring_interp_cntrl3D(base, arg0 + 0x10, 0, 1, D_001798B0);
}
#endif
