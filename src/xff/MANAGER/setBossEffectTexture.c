/* Parked draft: sets two GS TEX0 registers (6 and 7) for a 256x256 texture placed after the frame buffer. */
#ifdef NONMATCHING
extern int D_00130380;
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getFrameBufferSizeTBP(void);
extern void gsReg(int, long);
extern void gsRegBegin(void);
extern void gsRegEnd(void);

static inline long log2ceil(int v)
{
    long i = 0;
    int p = 1;
    while (p < v) {
        i++;
        p = 1 << i;
        if (i >= 0xB) {
            i = -1;
            break;
        }
    }
    return i;
}

void setBossEffectTexture(void)
{
    if (D_00130380 & 1) {
        int base;
        int w;
        int h;
        long a;
        long b;

        gsRegBegin();
        gsReg(0x3F, 1);
        gsReg(0x47, 0x51003);
        gsReg(0x42, (0x80L << 0x20) | 0x44);
        base = getFrameBufferSizeTBP();
        w = getDrawScreenWidth();
        h = getDrawScreenHeight();
        a = log2ceil(0x100);
        b = log2ceil(0x100);
        gsReg(6, (long)(base + ((w * h) >> 6)) | 0x10000 | ((a << 0x1E) | (b << 0x1A)) | (0x8000L << 0x13));
        gsReg(0x14, 0x60);
        gsReg(0x48, 0x51003);
        gsReg(0x43, (0x80L << 0x20) | 0x44);
        base = getFrameBufferSizeTBP();
        w = getDrawScreenWidth();
        h = getDrawScreenHeight();
        a = log2ceil(0x100);
        b = log2ceil(0x100);
        gsReg(7, (long)(base + ((w * h) >> 6)) | 0x10000 | ((a << 0x1E) | (b << 0x1A)) | (0x8000L << 0x13));
        gsReg(0x15, 0x60);
        gsRegEnd();
    }
}
#else
extern void setBossEffectTexture(void);
#endif
