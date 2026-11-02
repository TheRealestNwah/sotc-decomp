typedef struct DrawContext {
    char data[0x190];
} DrawContext;

typedef struct DrawContextSet {
    char pad0[0x1C];
    DrawContext *contexts;
} DrawContextSet;

extern int rootPtn;
extern DrawContextSet *D_0013617C;
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getFrameBufferSize(void);
extern int getZBufferAddressFBP(void);
extern DrawContextSet *iosCreateDC(void *, int);
extern void iosSetDCParam(DrawContext *, int, int, int, int);
extern void iosSetDCClearParam(DrawContext *, int, int, int, int, int);

void shadowInit(void)
{
    int width = getDrawScreenWidth();
    int height = getDrawScreenHeight();
    int i;

    D_0013617C = iosCreateDC(&rootPtn, 2);
    for (i = 0; i < 2; i++) {
        int fbp = (getFrameBufferSize() + 0x14000) >> 11;
        iosSetDCParam(&D_0013617C->contexts[i], fbp, getZBufferAddressFBP(), width, height);
        iosSetDCClearParam(&D_0013617C->contexts[i], 0, 0, 0, 0, 0x80);
    }
}
