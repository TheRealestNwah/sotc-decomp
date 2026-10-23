typedef struct {
    char pad[0x1C];
    int f1C;
    char pad20[0xC];
    int f2C;
    int f30;
    int f34;
    int f38;
    char pad3C[0x20];
    int f5C;
    char pad60[0xD0];
    char light_dir[0x40];
    char light[0x4084];
    float f41F4;
} GlState;

extern GlState D_00130480;
extern char D_001356D0[];
extern void setLight(void *, void *);
extern void iosDlPushLayer(int);
extern void iosDlChainTailCurrent(void *);
extern int iosDlPopLayer(void);

void glReset(void)
{
    GlState *gl = &D_00130480;
    int i;

    gl->f41F4 = 1.0f;
    setLight(gl->light, gl->light_dir);
    gl->f1C = 0;
    gl->f2C = 0;
    gl->f30 = 0;
    gl->f34 = 1;
    gl->f38 = 1;
    gl->f5C = 1;
    for (i = 0; i < 32; i++) {
        iosDlPushLayer(i);
        iosDlChainTailCurrent(D_001356D0);
        iosDlPopLayer();
    }
}
