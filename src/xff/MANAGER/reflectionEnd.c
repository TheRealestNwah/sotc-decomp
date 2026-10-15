extern void iosDlPushLayer(int layer);
extern void texResetVRAMRequest(int size);
extern void iosSetRootDC(void);
extern void iosDlPopLayer(void);

void reflectionEnd(void)
{
    iosDlPushLayer(0xF);
    texResetVRAMRequest(0);
    iosSetRootDC();
    iosDlPopLayer();
}
