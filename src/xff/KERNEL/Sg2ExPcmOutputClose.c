typedef struct { int a, b, c; void *buf; } PcmOut;
extern PcmOut B_000E2360;
extern int DIntr(void);
extern void EIntr(void);
extern void Sg2ExPcmOutputCtrl(int);
extern void free(void *);

int Sg2ExPcmOutputClose(void)
{
    void *p;
    int s = DIntr();
    Sg2ExPcmOutputCtrl(2);
    p = B_000E2360.buf;
    B_000E2360.buf = 0;
    if (s)
        EIntr();
    free(p);
    return 0;
}
