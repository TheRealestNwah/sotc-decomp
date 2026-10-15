extern int B_000C5B38;
extern void ____VolReflection(int *st);

void Sg2ExStAdpcmSetOutputMode(int *st, int mode)
{
    volatile int *p = &B_000C5B38;

    *p = mode;
    if (st != 0) {
        ____VolReflection(st);
    }
}
