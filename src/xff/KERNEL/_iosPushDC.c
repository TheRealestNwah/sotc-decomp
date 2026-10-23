typedef struct {
    char pad[0xD0];
    char sub[0xA0];
    int flags;
} DC;

extern int D_00040AE8;
extern void *B_00064C04[];
extern void *D_00040AE0;
extern void iosDlChainTailCurrent(void *);

void _iosPushDC(DC *dc, int sub)
{
    int *p = &D_00040AE8;
    int n = *p;
    B_00064C04[n + 1] = dc;
    *p = n + 1;
    iosDlChainTailCurrent(dc);
    if ((dc->flags & 1) && sub) {
        iosDlChainTailCurrent(dc->sub);
    }
    D_00040AE0 = dc;
}
