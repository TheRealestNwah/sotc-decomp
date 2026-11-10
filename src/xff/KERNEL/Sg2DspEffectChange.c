typedef struct { int a; int type; int endadr; short depthL; short depthR; int delay; int feedback; } DspEffect;
extern DspEffect B_000C5B08[];
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2RemoteSend(int, int, int, int);

int Sg2DspEffectChange(int i)
{
    int s = DIntr();
    int l = B_000C5B08[i].depthL * 0x7FFF / 127;
    int r = B_000C5B08[i].depthR * 0x7FFF / 127;
    int t;

    Sg2RemoteSend(0xB, i, B_000C5B08[i].endadr, 0);
    Sg2RemoteSend(0x10, i, B_000C5B08[i].feedback, 0);
    Sg2RemoteSend(0xF, i, B_000C5B08[i].delay, 0);
    Sg2RemoteSend(0xE, i, l, r);
    t = B_000C5B08[i].type;
    B_000C5B08[i].type = t & ~0x100;
    Sg2RemoteSend((t & 0x100) ? 0xD : 0xC, i, t & ~0x100, 0);
    if (s)
        EIntr();
    return 0;
}
