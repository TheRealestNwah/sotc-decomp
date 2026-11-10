typedef struct { int status, previous, unk8, vab, mod, x14, x18; char pad1C[52]; } Sep;
extern Sep B_000DD700[];
extern int B_000DE100;
extern void *memset(void *, int, unsigned int);
extern int Sg2CtrlEntryTickProcById(int, void (*)(void));
extern void Sg2SepTickProc(void);

int Sg2SepInit(void)
{
    char *base = (char *)B_000DD700;
    int *p = (int *)(base + 0x10);
    register int n __asm__("$17");
    register int off __asm__("$18") = 0;
    register int m1 __asm__("$19") = -1;

    for (n = 31; n >= 0; n--) {
        memset((char *)(off + (int)base), 0, sizeof(Sep));
        off += sizeof(Sep);
        p[-4] = 0;
        p[1] = m1;
        p[2] = m1;
        p[-1] = m1;
        p += sizeof(Sep) / 4;
    }
    B_000DE100 = 1;
    Sg2CtrlEntryTickProcById(1, Sg2SepTickProc);
    return 0;
}
