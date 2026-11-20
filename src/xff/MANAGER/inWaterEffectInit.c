typedef struct {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
} Ripple;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosFree(void *);
extern void *iosMallocAlign(void *, int, int);
extern float iosGetRandom(void);
extern float D_00136128;
extern float D_0013612C;
extern float D_00136130;
extern float D_00136134;
extern Ripple *D_00136148;
extern char rootPtn[];

void inWaterEffectInit(int alloc)
{
    int y;
    int x;

    if (alloc) {
        if (D_00136148) {
            iosFree(D_00136148);
        }
        D_00136148 = iosMallocAlign(rootPtn, 0x120C, 0x10);
    }
    for (y = 0; y < getDrawScreenHeight() / 32 + 1; y++) {
        for (x = 0; x < getDrawScreenWidth() / 64 + 1; x++) {
            D_00136148[(getDrawScreenWidth() / 64 + 1) * y + x].unk14 = 2.0f * (iosGetRandom() * 3.1415926f);
            D_00136148[(getDrawScreenWidth() / 64 + 1) * y + x].unk18 = 2.0f * (iosGetRandom() * 3.1415926f);
            D_00136148[(getDrawScreenWidth() / 64 + 1) * y + x].unkC = (2.0f * iosGetRandom() - 1.0f) * D_0013612C * 0.5f + D_00136128;
            D_00136148[(getDrawScreenWidth() / 64 + 1) * y + x].unk10 = (2.0f * iosGetRandom() - 1.0f) * D_0013612C * 0.5f + D_00136128;
            D_00136148[(getDrawScreenWidth() / 64 + 1) * y + x].unk8 = iosGetRandom() * D_00136134 + D_00136130;
        }
    }
}
