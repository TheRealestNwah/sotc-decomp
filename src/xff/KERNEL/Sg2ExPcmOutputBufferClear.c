typedef struct { int a, b, c, busy; int buf; int d; int pos; } PcmOut;
extern PcmOut B_000E2360;
extern int DIntr(void);
extern int EIntr(void);
static void func_0002E498(PcmOut *, int);
static void func_0002E5A0(PcmOut *, int);

int Sg2ExPcmOutputBufferClear(void)
{
    PcmOut *p = &B_000E2360;
    int s;
    if (p->busy != 0)
        return -1;
    s = DIntr();
    func_0002E498(p, p->buf);
    if (s)
        EIntr();
    func_0002E5A0(p, p->buf);
    p->pos = 0;
    return 0;
}
