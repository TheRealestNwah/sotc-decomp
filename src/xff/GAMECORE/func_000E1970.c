typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern void reset_double_spring_interp_cntrl(char *, float);
extern void GAMEUTIL_reset_status_manager(char *, int);

static void func_000E1970(char *self)
{
    reset_double_spring_interp_cntrl(self + 0x160, 1.0f);
    *(float *)(self + 0x180) = 1.0f;
    GAMEUTIL_reset_status_manager(self + 0x184, 0);
    *(s128 *)(self + 0x1A0) = ZeroPoint;
    *(s128 *)(self + 0x1B0) = ZUnitVector;
}
