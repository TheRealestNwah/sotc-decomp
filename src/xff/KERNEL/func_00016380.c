typedef struct {
    int x;
    int y;
    char pad8[8];
    int unk10;
    char pad14[0xC];
} LoadElem;

extern long iosGetTCount(void);
extern float iosGetSecondFromTCount(long);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(long reg, long data);
extern void gsRegEnd(void);
extern LoadElem *D_00040BCC;
extern int D_00040BD0;
extern int D_00040BD4;
extern float D_00040BD8;
extern long D_00040BE0;

/* Loading indicator: fades the ring of 16 dots in or out and advances the lit
   dot with the frame time, then draws the dots as GS sprites. The original
   reloads the globals after every element store, which only
   -fno-strict-aliasing reproduces (config/ee_cflags.json). */
static void func_00016380(void)
{
    float dt;
    int i;
    int j;
    int k;

    dt = iosGetSecondFromTCount(iosGetTCount() - D_00040BE0) * 30.0f;
    if (dt > 3.0f || dt < 0.0f) {
        dt = 0.0f;
    }
    D_00040BE0 = iosGetTCount();
    if (D_00040BD0 >= 2 && D_00040BCC != 0) {
        D_00040BD4 -= 4;
        if (D_00040BD4 <= 0) {
            D_00040BD4 = 0;
            D_00040BD0 = 0;
            return;
        }
    } else if (D_00040BD0 != 0) {
        D_00040BD4 += 4;
        if (D_00040BD4 >= 0x80) {
            D_00040BD4 = 0x80;
        }
    }
    if (D_00040BD0 != 0) {
        i = (int)D_00040BD8 + 1;
        D_00040BD8 += dt;
        for (; (int)D_00040BD8 >= i; i++) {
            k = i;
            for (j = 0; j < 16; j++) {
                D_00040BCC[j].unk10 -= 16;
                if (D_00040BCC[j].unk10 <= 0) {
                    D_00040BCC[j].unk10 = 0;
                }
            }
            while (k >= 16) {
                k -= 16;
            }
            D_00040BCC[k].unk10 = 0xFF;
        }
        while (D_00040BD8 >= 16.0f) {
            D_00040BD8 -= 16.0f;
        }
    }
    iosDlPushLayer(0x1F);
    gsRegBegin();
    gsReg(0x42, 0x8000000044);
    gsReg(0x47, 0x31001);
    gsReg(0x4A, 0);
    gsReg(0, 0x49);
    for (i = 0; i < 16; i++) {
        long c = D_00040BCC[i].unk10;
        gsReg(1, c | c << 8 | c << 16 | (long)D_00040BD4 << 24 | 0x3F80000000000000);
        gsReg(5, (D_00040BCC[i].x + 0x7FF0) | (long)(D_00040BCC[i].y + 0x8000) << 16 | 0xFFFFFF00000000);
        gsReg(5, (D_00040BCC[i].x + 0x8010) | (long)(D_00040BCC[i].y + 0x8000) << 16 | 0xFFFFFF00000000);
        gsReg(5, (D_00040BCC[i].x + 0x8000) | (long)(D_00040BCC[i].y + 0x7FF0) << 16 | 0xFFFFFF00000000);
        gsReg(5, (D_00040BCC[i].x + 0x8000) | (long)(D_00040BCC[i].y + 0x8010) << 16 | 0xFFFFFF00000000);
    }
    gsReg(0x47, 0x5164D);
    gsRegEnd();
    iosDlPopLayer();
}
