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
extern int D_001359B4;
extern void iosSetScreenEnv(void);
extern void vramDeleteBlock(void *);
extern void vramEnd(void);
extern void shadowReInit(void);
extern void windowReInit(void);
void graphFrameBufferReInitialize(void)
{
    if (D_001359B4 != 0) {
        int frameSize;
        iosSetScreenEnv();
        vramDeleteBlock(genv.image);
        vramDeleteBlock(genv.clut);
        vramDeleteBlock(genv.effect);
        vramEnd();
        vramInit();
        frameSize = getFrameBufferSizeTBP();
        genv.image = vramCreateBlock(RO_0013CD58, 0, frameSize, 0x3F3B - getFrameBufferSizeTBP());
        genv.clut = vramCreateBlock(RO_0013CD60, 1, 0x3F3B, 0x7D);
        genv.effect = vramCreateBlock(RO_0013CD68, 0, 0x3FC0, 0x40);
        shadowReInit();
        windowReInit();
        inWaterEffectInit(0);
        D_001359B4 = 0;
    }
}
