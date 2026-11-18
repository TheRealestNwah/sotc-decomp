typedef int sceVu0IVECTOR[4] __attribute__((aligned(16)));

extern void gsRegBegin(void);
extern void gsReg(int reg, unsigned long value);
extern void gsRegEnd(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern unsigned long getFrameBufferSizeFBP(void);
extern int getFrameBufferSizeTBP(void);
extern int getDrawBufferAddressFBP(void);
extern int getDrawBufferAddressTBP(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void spriteTexFast(int x0, int y0, int x1, int y1, int rgb, int *uv, int *color, int a7);
extern float D_00136144;

#define SCE_GS_SET_FRAME(fbp, fbw, psm, fbmsk) \
    ((unsigned long)(fbp) | ((unsigned long)(fbw) << 16) | ((unsigned long)(psm) << 24) | ((unsigned long)(fbmsk) << 32))
#define SCE_GS_SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld) \
    ((unsigned long)(tbp) | ((unsigned long)(tbw) << 14) | ((unsigned long)(psm) << 20) \
     | ((unsigned long)(tw) << 26) | ((unsigned long)(th) << 30) | ((unsigned long)(tcc) << 34) \
     | ((unsigned long)(tfx) << 35) | ((unsigned long)(cbp) << 37) | ((unsigned long)(cpsm) << 51) \
     | ((unsigned long)(csm) << 55) | ((unsigned long)(csa) << 56) | ((unsigned long)(cld) << 61))
#define SCE_GS_SET_XYOFFSET(ofx, ofy) ((unsigned long)(ofx) | ((unsigned long)(ofy) << 32))
#define SCE_GS_SET_SCISSOR(scax0, scax1, scay0, scay1) \
    ((unsigned long)(scax0) | ((unsigned long)(scax1) << 16) | ((unsigned long)(scay0) << 32) \
     | ((unsigned long)(scay1) << 48))

void refractionBegin(float brightness)
{
    int width;
    int height;
    int center = 0x800;
    int texOfs = 4;

    width = getDrawScreenWidth();
    height = getDrawScreenHeight();
    D_00136144 = brightness;
    iosDlPushLayer(0x13);
    gsRegBegin();
    gsReg(0x4C, SCE_GS_SET_FRAME(getFrameBufferSizeFBP(), 4, 0, 0));
    gsReg(0x18, 0x0000780000007800);
    gsReg(0x40, 0x00FF000000FF0000);
    gsReg(0x4A, 0);
    gsReg(0x3B, 0x0000008000000080);
    gsReg(0x47, 0x31001);
    gsReg(0x42, 0x44);
    gsReg(0x14, 0x60);
    {
        sceVu0IVECTOR rect = { -center, -center, center * 2, center * 2 };
        sceVu0IVECTOR color = { 0x80, 0x80, 0x80, 0x80 };
        sceVu0IVECTOR uv = { texOfs, texOfs, width << 4, height << 4 };

        gsReg(6, SCE_GS_SET_TEX0(getDrawBufferAddressTBP(), width / 64, 1, 9, 9, 1, 0, 0, 0, 0, 0, 0));
        spriteTexFast(rect[0], rect[1], rect[2], rect[3], 0xFFFFFF, uv, color, 0);
    }
    gsReg(0x47, 0x5000D);
    gsReg(6, SCE_GS_SET_TEX0(getFrameBufferSizeTBP(), texOfs, 1, 8, 8, 1, 0, 0, 0, 0, 0, 0));
    gsReg(0x4C, SCE_GS_SET_FRAME(getDrawBufferAddressFBP(), (width >> 6) & 0x3F, 0, 0));
    gsReg(0x18, SCE_GS_SET_XYOFFSET((center - width / 2) << 4, (center - height / 2) << 4));
    gsReg(0x40, SCE_GS_SET_SCISSOR(0, width - 1, 0, height - 1));
    gsReg(8, 5);
    gsRegEnd();
    iosDlPopLayer();
}
