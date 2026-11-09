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

static inline void setLoadElem(LoadElem *e, LoadVec v)
{
    e->x = (int)(v.x * 16.0f);
    e->y = (int)(v.y * 16.0f);
    e->unk10 = 0;
}

/* Parked: 147 diffs: loader vector copy scheduling and register allocation differ */
#ifdef NONMATCHING
void set_nowloadingflag(int flag)
{
    int i;
    float a;
    LoadVec v;
    LoadVec t;

    if (D_00040BD0 != 1 && flag != 0) {
        if (D_00040BCC == 0) {
            D_00040BCC = iosMallocAlign(rootPtn, 0x200, 0x10);
        }
        if (D_00040BD0 == 0) {
            for (i = 0; i < 16; i++) {
                a = 2.0f * ((float)i * 3.1415925f) * 0.0625f;
                v.x = (float)(getDrawScreenWidth() / 2 - 36) +
                      iosGetCosf(a) * 20.0f * (float)getDrawScreenWidth() / (float)getDispScreenWidth();
                v.y = (float)(getDrawScreenHeight() / 2 - 36) +
                      iosGetSinf(a) * 20.0f * (float)getDrawScreenHeight() / (float)getDispScreenHeight();
                v.z = 0;
                v.w = 1.0f;
                t = v;
                D_00040BCC[i].x = (int)(t.x * 16.0f);
                D_00040BCC[i].y = (int)(t.y * 16.0f);
                D_00040BCC[i].unk10 = 0;
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
#else
extern void set_nowloadingflag(int flag);
#endif
