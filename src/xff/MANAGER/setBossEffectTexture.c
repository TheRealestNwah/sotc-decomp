extern int D_00130380;
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getFrameBufferSizeTBP(void);
extern void gsReg(int, unsigned long);
extern void gsRegBegin(void);
extern void gsRegEnd(void);

static inline int log2i(int v)
{
    int i;

    for (i = 0; i < 11; i++) {
        if (!((1 << i) < v)) {
            return i;
        }
    }
    return -1;
}

void setBossEffectTexture(void)
{
    if (D_00130380 & 1) {
        gsRegBegin();
        gsReg(0x3F, 1);
        gsReg(0x47, 0x51003);
        gsReg(0x42, ((unsigned long)0x80 << 32) | 0x44);
        gsReg(6, (unsigned long)(getFrameBufferSizeTBP() + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 6)) | 0x10000
                     | ((unsigned long)log2i(0x100) << 26) | ((unsigned long)log2i(0x100) << 30) | ((unsigned long)0x8000 << 19));
        gsReg(0x14, 0x60);
        gsReg(0x48, 0x51003);
        gsReg(0x43, ((unsigned long)0x80 << 32) | 0x44);
        gsReg(7, (unsigned long)(getFrameBufferSizeTBP() + ((getDrawScreenWidth() * getDrawScreenHeight()) >> 6)) | 0x10000
                     | ((unsigned long)log2i(0x100) << 26) | ((unsigned long)log2i(0x100) << 30) | ((unsigned long)0x8000 << 19));
        gsReg(0x15, 0x60);
        gsRegEnd();
    }
}
