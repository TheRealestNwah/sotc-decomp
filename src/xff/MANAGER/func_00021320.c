typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    float f10;
    float f14;
    float f18;
} RefGrid;

extern float D_00136138;
extern int D_STR_0013613C;
extern int D_00136140;
extern float D_00136144;
extern RefGrid *D_00136148;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern float iosGetCosf(float);
extern float iosGetSinf(float);
extern void gsRegBegin(void);
extern void gsReg(int, unsigned long);
extern void gsRegEnd(void);

#define GX (getDrawScreenWidth() / 64)
#define GY (getDrawScreenHeight() / 32)
#define G(i, j) D_00136148[GX * (j) + (j) + (i)]
#define FTOI4(f) (((int)(f) << 4) + (int)(((f) - (float)(int)(f)) * 16.0f))

static void func_00021320(void)
{
    int i;
    int j;
    int w;
    int h;

    for (i = 0; i < GX + 1; i++) {
        for (j = 0; j < GY + 1; j++) {
            G(i, j).f14 += G(i, j).fC * D_00136144 * 30.0f;
            G(i, j).f18 += G(i, j).f10 * D_00136144 * 30.0f;
            G(i, j).f0 = (float)i / (float)GX;
            G(i, j).f4 = (float)j / (float)GY;
            G(i, j).f0 += G(i, j).f8 * iosGetCosf(G(i, j).f14) * D_00136138;
            G(i, j).f4 += G(i, j).f8 * iosGetSinf(G(i, j).f18);
        }
    }
    gsRegBegin();
    w = getDrawScreenWidth();
    h = getDrawScreenHeight();
    gsReg(0x47, 0x51001);
    gsReg(0x42, 0x44);
    gsReg(8, 5);
    gsReg(1, (unsigned long)D_00136140 | ((unsigned long)D_00136140 << 8) | ((unsigned long)D_00136140 << 16) |
                 ((unsigned long)D_STR_0013613C << 24) | ((unsigned long)0x3F800000 << 32));
    for (i = 0; i < GX; i++) {
        gsReg(0, 0x54);
        for (j = 0; j < GY + 1; j++) {
            float x;
            float y;
            float x2;

            int ty;
            int tx;

            gsReg(2, (unsigned long)*(unsigned int *)&G(i, j).f0 | ((unsigned long)*(unsigned int *)&G(i, j).f4 << 32));
            x = (float)(i * 64) - (float)(w >> 1) + 2048.0f;
            y = (float)(j * 32) - (float)(h >> 1) + 2048.0f;
            ty = (int)y;
            tx = (int)x;
            y -= (float)ty;
            x -= (float)tx;
            ty = (ty << 4) + (int)(y * 16.0f);
            tx = (tx << 4) + (int)(x * 16.0f);
            gsReg(4, (unsigned long)tx | ((unsigned long)ty << 16) | ((unsigned long)0xFFFFFFFF << 32));
            gsReg(2, (unsigned long)*(unsigned int *)&(&G(i, j))[1].f0 |
                         ((unsigned long)*(unsigned int *)&(&G(i, j))[1].f4 << 32));
            x2 = (float)(i * 64 + 64) - (float)(w >> 1) + 2048.0f;
            tx = (int)x2;
            x2 -= (float)tx;
            tx = (tx << 4) + (int)(x2 * 16.0f);
            gsReg(4, (unsigned long)tx | ((unsigned long)ty << 16) | ((unsigned long)0xFFFFFFFF << 32));
        }
    }
    gsReg(0x47, 0x5100D);
    gsRegEnd();
}
