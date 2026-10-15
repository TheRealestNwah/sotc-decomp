extern void iosDlPushLayer(int);
extern void gsRegBegin(void);
extern void gsReg(int, unsigned long);
extern void gsRegEnd(void);
extern void iosSetRootDC(void);
extern void iosDlPopLayer(void);

void waterRefractionEnd(void)
{
    iosDlPushLayer(9);
    gsRegBegin();
    gsReg(0x49, 0);
    gsReg(0x42, 0x44);
    gsReg(0x47, 0x5078D);
    gsRegEnd();
    iosSetRootDC();
    iosDlPopLayer();
}
