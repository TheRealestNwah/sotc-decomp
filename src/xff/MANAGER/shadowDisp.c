extern int D_00136170;
extern int D_00136178;
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, long);
extern void iosDlChainTailCurrent(int);
extern int iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern void transMicroCode(int);

void shadowDisp(int arg0, int *arg1, int a2, int a3, int a4, int a5, int a6)
{
    if (arg1 != 0) {
        if (D_00136170 != 0) {
            if (a6 != 0) {
                iosDlPushLayer((D_00136178 != 0) ? 3 : 7);
                transMicroCode(5);
                iosDlChainTailCurrent(arg0);
                if (D_00136178 != 0) {
                    gsRegBegin();
                    gsReg(0x42, 0x4000000064L);
                    gsReg(0x47, 0x51001);
                    gsReg(0x43, 0x4000000064L);
                    gsReg(0x48, 0x51001);
                    gsRegEnd();
                }
                transMicroCode(9);
                iosDlChainTailCurrent(arg1[7]);
                iosDlPopLayer();
                __asm__ __volatile__("");
            } else {
                iosDlPushLayer((D_00136178 != 0) ? 3 : 7);
                transMicroCode(0);
                iosDlChainTailCurrent(arg0);
                if (D_00136178 != 0) {
                    gsRegBegin();
                    gsReg(0x42, 0x4000000064L);
                    gsReg(0x47, 0x51001);
                    gsReg(0x43, 0x4000000064L);
                    gsReg(0x48, 0x51001);
                    gsRegEnd();
                }
                transMicroCode(8);
                iosDlChainTailCurrent(arg1[7]);
                iosDlPopLayer();
                __asm__ __volatile__("");
            }
        }
    }
}
