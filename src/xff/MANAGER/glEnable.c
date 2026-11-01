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

void glEnable(int cap)
{
    int on = 1;

    switch (cap) {
    case 0:
        D_00130498 = on;
        break;
    case 1:
        D_001304B4 = on;
        break;
    case 2:
        D_001304B8 = on;
        break;
    case 3:
        D_0013049C = on;
        break;
    case 4:
        D_001304A8 = on;
        break;
    case 7:
        D_001304A0 = on;
        break;
    case 8:
        D_001304A4 = on;
        break;
    case 9:
        D_001304B0 = on;
        break;
    case 10:
        D_00130480.f1B0_1 = on;
        break;
    case 19:
        D_001304DC = on;
        break;
    case 20:
        D_001304AC = on;
        break;
    }
}
