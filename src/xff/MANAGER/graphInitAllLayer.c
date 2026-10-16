extern char D_00135850[];
extern int iosDlGetLayerNum(void);
extern void iosDlPushLayer(int);
extern int iosDlGetWorkBufId(void);
extern void iosDlChainTailCurrent(void *);
extern void iosDlPopLayer(void);

void graphInitAllLayer(void)
{
    int i;

    for (i = 0; i < iosDlGetLayerNum(); i++) {
        iosDlPushLayer(i);
        iosDlChainTailCurrent(D_00135850 + iosDlGetWorkBufId() * 0xB0);
        iosDlPopLayer();
    }
}
