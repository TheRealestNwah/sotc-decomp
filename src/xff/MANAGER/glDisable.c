typedef struct {
    char pad[0x1B0];
    unsigned long f1B0_0 : 1;
    unsigned long f1B0_1 : 1;
} GlFlags;

extern GlFlags D_00130480;
extern int D_00130498;
extern int D_0013049C;
extern int D_001304A0;
extern int D_001304A4;
extern int D_001304A8;
extern int D_001304AC;
extern int D_001304B0;
extern int D_001304B4;
extern int D_001304B8;
extern int D_001304DC;

void glDisable(int cap)
{
    switch (cap) {
    case 0:
        D_00130498 = 0;
        break;
    case 1:
        D_001304B4 = 0;
        break;
    case 2:
        D_001304B8 = 0;
        break;
    case 3:
        D_0013049C = 0;
        break;
    case 4:
        D_001304A8 = 0;
        break;
    case 7:
        D_001304A0 = 0;
        break;
    case 8:
        D_001304A4 = 0;
        break;
    case 9:
        D_001304B0 = 0;
        break;
    case 10:
        D_00130480.f1B0_1 = 0;
        break;
    case 19:
        D_001304DC = 0;
        break;
    case 20:
        D_001304AC = 0;
        break;
    }
}
