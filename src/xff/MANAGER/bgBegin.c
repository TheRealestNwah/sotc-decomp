extern void iosDlPushLayer(int layer);
extern void texResetVRAMRequest(int size);
extern void iosSetRootDC(void);
extern void iosDlPopLayer(void);

void bgBegin(void)
{
    iosDlPushLayer(1);
    texResetVRAMRequest(0x400);
    iosSetRootDC();
    iosDlPopLayer();
}
