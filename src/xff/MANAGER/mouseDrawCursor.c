extern float D_00137724;
extern float iosGetSecondFromTCount(int);
extern int iosGetTCountExtension(void);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, long long);
extern void spriteDraw(int, int, int, int, int, int, int, int, int, int, int, int, int);

void mouseDrawCursor(int type, float x, float y)
{
    int ox, oy, u, t;

    if (iosGetSecondFromTCount(iosGetTCountExtension()) - D_00137724 > 5.0f) {
        return;
    }
    if (type == 6) {
        return;
    }
    gsRegBegin();
    gsReg(8, 5);
    gsReg(0x42, 0x8000000044LL);
    gsReg(0x14, 0);
    gsReg(0x47, 0x30000);
    switch (type) {
    case 1:
        ox = -4; oy = -8; t = 0x20; u = 0x10;
        break;
    case 2:
        ox = -8; oy = -4; t = 0x30; u = 0;
        break;
    case 3:
        ox = -8; oy = -8; t = 0x30; u = 0x10;
        break;
    case 4:
        ox = -8; oy = -8; t = 0x20; u = 0x20;
        break;
    default:
        ox = 0; oy = 0; t = 0x20; u = 0;
        break;
    }
    spriteDraw((int)(x + (float)ox), (int)(y + (float)oy), 0x10, 0x10, 0xFFFFFF, t, u, t + 0x10, u + 0x10, 0xFF, 0xFF, 0xFF, 0x80);
    gsReg(0x47, 0x5000D);
    gsRegEnd();
}
