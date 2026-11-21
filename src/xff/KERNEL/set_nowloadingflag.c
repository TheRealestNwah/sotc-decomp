typedef struct {
    float x, y;
    int z;
    float w;
} __attribute__((aligned(8))) LoadVec;

typedef struct {
    int x;
    int y;
    char pad8[8];
    int unk10;
    char pad14[0xC];
} LoadElem;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getDispScreenWidth(void);
extern int getDispScreenHeight(void);
extern float iosGetCosf(float);
extern float iosGetSinf(float);
extern void *iosMallocAlign(void *, int, int);
extern char rootPtn[];
extern LoadElem *D_00040BCC;
extern int D_00040BD0;
extern int D_00040BD8;

void set_nowloadingflag(int flag)
{
    int i;
    float a;
    union { LoadVec v; int i[4]; } t;
    LoadVec v;
    float fi;
    int sw;

    if (D_00040BD0 != 1 && flag != 0) {
        if (D_00040BCC == 0) {
            D_00040BCC = iosMallocAlign(rootPtn, 0x200, 0x10);
        }
        if (D_00040BD0 == 0) {
            for (i = 0; i < 16; i++) {
                fi = (float)i;
                sw = getDrawScreenWidth();
                a = 2.0f * (fi * 3.1415927f) * 0.0625f;
                v.x = (float)(sw / 2 - 36) +
                      iosGetCosf(a) * 20.0f * (float)getDrawScreenWidth() / (float)getDispScreenWidth();
                v.y = (float)(getDrawScreenHeight() / 2 - 36) +
                      iosGetSinf(a) * 20.0f * (float)getDrawScreenHeight() / (float)getDispScreenHeight();
                v.z = 0;
                v.w = 1.0f;
                t.v = v;
                ((int *)&D_00040BCC[i])[0] = (int)(t.v.x * 16.0f);
                ((int *)&D_00040BCC[i])[1] = (int)(t.v.y * 16.0f);
                ((int *)&D_00040BCC[i])[4] = 0;
            }
            D_00040BD8 = 0;
        }
        D_00040BD0 = flag;
    } else if (D_00040BD0 != 0) {
        if (flag == 0) {
            D_00040BD0++;
        } else if (flag == -1) {
            D_00040BD0 = 0;
        }
    }
}
