/* ~11 diffs (2 relocations), same length (150 words). Feedback-blur screen pass (template: drawDemoBar): skip while D_00135420 counts down, else under layer 0x1D writes GS regs (alpha via 0x42, TEX0 from the disp-buffer TBP with TW of the disp height and width as TBW dispW/64, two sprite-corner XYZ pairs around 0x800 +- half the draw size, UV box dispW*16+8 / dispH*16+8) and pops the layer. Matches except the TEX0 or-chain scheduling and which register holds alpha<<32 (Original: $v1 for the alpha shift, twh << 26 computed after the movn of the TBW divide). Needed: getTWH(dispH) first, an inline_fn add for the +0x800 corners (stops gcc distributing the *16), and `return` after iosDlPopLayer so it becomes the tail call. */
extern int D_00130420;
extern int getDispScreenWidth(void);
extern int getDispScreenHeight(void);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDispBufferAddressTBP(void);
extern long getTWH(int);
extern void gsReg(int, long);
static inline int inline_fn(int a, int b)
{
    return a + b;
}
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);


void feedbackBlur(int alpha)
{
    int dispW = getDispScreenWidth();
    int dispH = getDispScreenHeight();
    int drawW = getDrawScreenWidth();
    int drawH = getDrawScreenHeight();
    int hw = drawW >> 1;
    int hh = drawH >> 1;

    int c = D_00130420;

    if (c > 0) {
        D_00130420 = c - 1;
        return;
    }
    if (alpha != 0) {
        long m;
        long tbp;
        long twl;
        long twh;

        m = -1L;
        m = m << 0x20;
        iosDlPushLayer(0x1D);
        gsRegBegin();
        gsReg(0x42, (((long)alpha) << 0x20) | 0x64);
        gsReg(0x47, 0x31001);
        gsReg(0x49, 0);
        gsReg(0x3B, (0x80L << 0x20) | 0x80);
        gsReg(0x14, 0x20);
        tbp = getDispBufferAddressTBP();
        twl = getTWH(dispH);
        twh = getTWH(dispW);
        gsReg(6, (tbp | (twl << 30)) | ((twh << 26) | ((long)(dispW / 64) << 14)));
        gsReg(0, 0x156);
        gsReg(1, (((0x3F800000L << 0x10) | 0x8080) << 0x10) | 0x8080);
        gsReg(3, 0x80008);
        gsReg(4, (((0x800 - hw) * 0x10) | (((long)((0x800 - hh) * 0x10)) << 0x10)) | m);
        gsReg(3, (dispW * 0x10 + 8) | (((long)(dispH * 0x10 + 8)) << 0x10));
        gsReg(4, (inline_fn(hw, 0x800) * 0x10) | (((long)(inline_fn(hh, 0x800) * 0x10)) << 0x10) | m);
        gsReg(0x42, (0x80L << 0x20) | 0x44);
        gsReg(0x47, 0x5178D);
        gsReg(0x49, 1);
        gsRegEnd();
        iosDlPopLayer();
        return;
    }
}

