static char D_00135850[0xB0 * 2];
extern void iosDlPushLayer(int);
extern int iosDlGetWorkBufId(void);
extern void iosDlChainTailCurrent(void *);
extern void iosDlPopLayer(void);

void graphInitLayer(int layer)
{
    iosDlPushLayer(layer);
    iosDlChainTailCurrent(D_00135850 + iosDlGetWorkBufId() * 0xB0);
    iosDlPopLayer();
}
