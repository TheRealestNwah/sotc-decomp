typedef struct { void *image, *clut, *effect; } GraphEnvironment;
extern GraphEnvironment genv;
extern int D_0013583C;
extern char RO_0013CD58[], RO_0013CD60[], RO_0013CD68[];
extern void vramInit(void);
extern int getFrameBufferSizeTBP(void);
extern void *vramCreateBlock(const char *, int, int, int);
extern int iosDlGetLayerNum(void);
extern void texInit(int);
extern void modelInit(int);
extern void kInit(void);
extern void windowInit(void);
extern void lineObjectInit(void);
extern void shadowInit(void);
extern void inWaterEffectInit(int);
extern void zFogInit(void);
void graphInit(void)
{
    int frameSize;
    vramInit();
    frameSize = getFrameBufferSizeTBP();
    genv.image = vramCreateBlock(RO_0013CD58, 0, frameSize, 0x3F3B - getFrameBufferSizeTBP());
    genv.clut = vramCreateBlock(RO_0013CD60, 1, 0x3F3B, 0x7D);
    genv.effect = vramCreateBlock(RO_0013CD68, 0, 0x3FC0, 0x40);
    texInit(iosDlGetLayerNum());
    modelInit(iosDlGetLayerNum());
    kInit();
    windowInit();
    lineObjectInit();
    shadowInit();
    inWaterEffectInit(1);
    zFogInit();
    D_0013583C = 1;
}
