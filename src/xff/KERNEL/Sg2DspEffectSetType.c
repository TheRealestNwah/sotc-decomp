typedef struct { int a; int type; int endadr; int b; int delay; int feedback; } DspEffect;
extern DspEffect B_000C5B08[];
extern int DIntr(void);
extern void EIntr(void);

int Sg2DspEffectSetType(int i, int v)
{
    int old;
    int s = DIntr();
    old = B_000C5B08[i].type;
    B_000C5B08[i].type = v;
    if (s)
        EIntr();
    return old;
}
