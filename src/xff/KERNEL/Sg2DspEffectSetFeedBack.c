typedef struct { int feedback; char pad[0x14]; } DspEffect;
extern DspEffect B_000C5B1C[];
extern int DIntr(void);
extern void EIntr(void);

int Sg2DspEffectSetFeedBack(int i, int v)
{
    int old;
    int s = DIntr();
    old = B_000C5B1C[i].feedback;
    B_000C5B1C[i].feedback = v;
    if (s)
        EIntr();
    return old;
}
