#define SCE_GS_SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld) \
    ((unsigned long)(tbp) | ((unsigned long)(tbw) << 14) | ((unsigned long)(psm) << 20) \
     | ((unsigned long)(tw) << 26) | ((unsigned long)(th) << 30) | ((unsigned long)(tcc) << 34) \
     | ((unsigned long)(tfx) << 35) | ((unsigned long)(cbp) << 37) | ((unsigned long)(cpsm) << 51) \
     | ((unsigned long)(csm) << 55) | ((unsigned long)(csa) << 56) | ((unsigned long)(cld) << 61))

extern int D_00130420;
extern int getDispScreenWidth(void);
extern int getDispScreenHeight(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDispBufferAddressTBP(void);
extern int getTWH(int);
extern void gsReg(int, long);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern void spriteSetTextureCoordinateST(void *s, float u, float v, float w, float h);

void feedbackBlur2(int alpha)
{
    float sprite[20];
    int dispW = getDispScreenWidth();
    int dispH = getDispScreenHeight();
    int drawW = getDrawScreenWidth();
    int drawH = getDrawScreenHeight();
    int hw = drawW >> 1;
    int hh = drawH >> 1;
    long m;

    if (D_00130420 > 0) {
        D_00130420--;
        return;
    }
    if (alpha == 0) {
        return;
    }
    m = -1L;
    m = m << 0x20;
    iosDlPushLayer(0x1D);
    sprite[14] = drawW;
    sprite[15] = drawH;
    spriteSetTextureCoordinateST(sprite, 0.0f, 0.0f, 1.0f, dispH * 0.001953125f);
    gsRegBegin();
    gsReg(0x49, 0);
    gsReg(0x3B, (0x80L << 0x20) | 0x80);
    gsReg(0x14, 0x60);
    gsReg(6, SCE_GS_SET_TEX0(getDispBufferAddressTBP(), dispW / 64, 0, getTWH(dispW), getTWH(dispH), 0, 0, 0, 0, 0, 0, 0));
    gsRegEnd();
    gsRegBegin();
    gsReg(0, 0x156);
    gsReg(1, ((long)alpha << 24) | (((0x3F800000L << 0x10) | 0x80) << 0x10) | 0x8080);
    gsReg(3, 0);
    gsReg(4, (((0x800 - hw) * 0x10 - 8) | (((long)((0x800 - hh) * 0x10 - 0x18)) << 0x10)) | m);
    gsReg(3, (dispW * 0x10) | (((long)(dispH * 0x10)) << 0x10));
    gsReg(4, ((hw + 0x800) * 0x10 - 8) | (((long)((hh + 0x800) * 0x10 - 0x18)) << 0x10) | m);
    gsRegEnd();
    gsRegBegin();
    gsReg(0x42, (0x80L << 0x20) | 0x44);
    gsReg(0x47, 0x5178D);
    gsReg(0x49, 1);
    gsRegEnd();
    iosDlPopLayer();
}
