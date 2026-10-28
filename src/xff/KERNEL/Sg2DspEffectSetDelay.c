typedef struct { int delay; int feedback; char pad[0x10]; } DspEffect;
extern DspEffect B_000C5B18[];
extern int DIntr(void);
extern int EIntr(void);

int Sg2DspEffectSetDelay(int i, int v)
{
    int old;
    int s = DIntr();
    old = B_000C5B18[i].delay;
    B_000C5B18[i].delay = v;
    if (s)
        EIntr();
    return old;
}
