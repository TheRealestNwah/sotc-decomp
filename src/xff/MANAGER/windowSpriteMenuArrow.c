extern long iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(long);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texTransRequest(void *, int, int);
extern void gsRegBegin(void);
extern void gsReg(int, long);
extern void gsRegEnd(void);
extern void *D_00139B80;

void windowSpriteMenuArrow(char *win, int x, int y)
{
    float t;
    float ofs;
    float fx, fy;
    long z;
    int ix;

    t = iosGetSecondFromTCount(iosGetTCountExtension());
    t = t + t;
    ofs = (t - (float)(int)t) * 8.0f - 18.0f;
    iosDlPushLayer(0x1E);
    if (D_00139B80 != 0)
        texTransRequest(D_00139B80, 3, 0);
    z = 0xFFFE524FL << 32;
    gsRegBegin();
    fx = (float)x + *(float *)(win + 0x198) - *(float *)(win + 0x26C) * 0.5f;
    fy = (float)y + *(float *)(win + 0x19C) - *(float *)(win + 0x270) * 0.5f;
    gsReg(0x47, 0x30000);
    fx += ofs;
    gsReg(0, 0x4D);
    gsReg(1, 0x3F800000700080C0L);
    ix = (int)((fx + 8.0f + 2048.0f) * 16.0f);
    gsReg(4, ix | ((long)(int)((fy + 3.0f + 2048.0f) * 16.0f) << 16) | z);
    gsReg(4, (int)((fx + 11.0f + 2048.0f) * 16.0f) | ((long)(int)((fy + 7.5f + 2048.0f) * 16.0f) << 16) | z);
    gsReg(4, ix | ((long)(int)((fy + 12.0f + 2048.0f) * 16.0f) << 16) | z);
    gsReg(0x47, 0x5140B);
    gsRegEnd();
    iosDlPopLayer();
}
