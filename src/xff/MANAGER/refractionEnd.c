extern void iosDlPushLayer(int);
extern int *getFogUnderWater(void);
extern void func_00021320(void);
extern void gsRegBegin(void);
extern void gsReg(int, unsigned long);
extern void gsRegEnd(void);
extern void iosSetRootDC(void);
extern void iosDlPopLayer(void);

void refractionEnd(void)
{
    iosDlPushLayer(0x13);
    if (*getFogUnderWater() != 0)
        func_00021320();
    gsRegBegin();
    gsReg(0x42, 0x44);
    gsReg(0x47, 0x5078D);
    gsRegEnd();
    iosSetRootDC();
    iosDlPopLayer();
}
