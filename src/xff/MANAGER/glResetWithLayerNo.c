extern void iosDlChainTailCurrent(void *);
extern void iosDlPopLayer();
extern void iosDlPushLayer(int);
extern unsigned char D_001356D0[];

void glResetWithLayerNo(int layer)
{
    iosDlPushLayer(layer);
    iosDlChainTailCurrent(D_001356D0);
    iosDlPopLayer();
}
