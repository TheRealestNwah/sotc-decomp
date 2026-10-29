typedef struct { char bytes[0xB0]; } DisplayContext;
typedef struct { char pad0[0x24]; float time; } GraphEnvironment;
extern int D_0013583C;
extern float D_001359B0;
extern GraphEnvironment genv;
extern DisplayContext D_00135850[];
extern void effectReset(void);
extern void texReset(int, float);
extern void glReset(void);
extern void windowSetMouseStatus(void);
extern void resetMicroCodeManager(void);
extern void iosDlPushLayer(int);
extern int iosDlGetWorkBufId(void);
extern void iosDlChainTailCurrent(void *);
extern void iosDlPopLayer(void);
extern int iosDlGetLayerNum(void);
void graphFrameInit(float delta)
{
    if (D_0013583C != 0) {
        int layer;
        effectReset();
        D_001359B0 = delta;
        genv.time += delta;
        texReset(1, delta);
        glReset();
        windowSetMouseStatus();
        resetMicroCodeManager();
        for (layer = 0; layer < iosDlGetLayerNum(); layer++) {
            iosDlPushLayer(layer);
            iosDlChainTailCurrent(&D_00135850[iosDlGetWorkBufId()]);
            iosDlPopLayer();
        }
    }
}
