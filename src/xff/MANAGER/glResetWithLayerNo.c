extern void iosDlChainTailCurrent(void *);
extern void iosDlPopLayer();
extern void iosDlPushLayer();
extern unsigned char D_001356D0[];

void glResetWithLayerNo(void)
{
    iosDlPushLayer();
    iosDlChainTailCurrent(D_001356D0);
    iosDlPopLayer();
}
