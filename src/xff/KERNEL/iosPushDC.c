extern int D_00040AE8;
extern void *B_00064C04[];
extern void *D_00040AE0;
extern void iosDlChainTailCurrent(void *);

void iosPushDC(void *dc)
{
    int *p = &D_00040AE8;
    int n = *p;
    B_00064C04[n + 1] = dc;
    *p = n + 1;
    iosDlChainTailCurrent(dc);
    D_00040AE0 = dc;
}
