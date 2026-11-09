/* Parked: 18 words off, only the branch layout of the cursor-type chain differs (original shares a tail via goto). */
#ifdef NONMATCHING
extern float D_00137724;
extern void gsReg(int, long);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern float iosGetSecondFromTCount(int);
extern int iosGetTCountExtension(void);
extern void spriteDraw(int, int, int, int, int, int, int, int, int, int, int, int, int);

void mouseDrawCursor(int arg0, float x, float y)
{
    int ox, oy, u, v;

    if (iosGetSecondFromTCount(iosGetTCountExtension()) - D_00137724 > 5.0f)
        return;
    if (arg0 == 6)
        return;
    gsRegBegin();
    gsReg(8, 5);
    gsReg(0x42, (0x80L << 0x20) | 0x44);
    gsReg(0x14, 0);
    gsReg(0x47, 0x30000);
    ox = -8;
    oy = -4;
    u = 0x30;
    v = 0;
    if (arg0 != 2) {
        if (arg0 < 3) {
            ox = -4;
            oy = -8;
            u = 0x20;
            v = 0x10;
            if (arg0 != 1) {
                ox = 0;
                oy = 0;
                u = 0x20;
                v = 0;
            }
        } else {
            oy = -8;
            u = 0x30;
            v = 0x10;
            if (arg0 != 3) {
                if (arg0 != 4) {
                    ox = 0;
                    oy = 0;
                    u = 0x20;
                    v = 0;
                } else {
                    u = 0x20;
                    v = 0x20;
                }
            }
        }
    }
    spriteDraw((int)(x + (float)ox), (int)(y + (float)oy), 0x10, 0x10, 0xFFFFFF, u, v, u + 0x10, v + 0x10, 0xFF, 0xFF, 0xFF, 0x80);
    gsReg(0x47, 0x5000D);
    gsRegEnd();
}
#else
extern void mouseDrawCursor(int, float, float);
#endif
