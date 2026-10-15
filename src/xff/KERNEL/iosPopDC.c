extern int D_00040AE8;
extern void *B_00064C04[];
extern void *D_00040AE0;
extern void iosDlChainTailCurrent(void *);

void iosPopDC(void)
{
    void *dc;
    D_00040AE8--;
    dc = B_00064C04[D_00040AE8];
    iosDlChainTailCurrent(dc);
    D_00040AE0 = dc;
}
