typedef struct {
    char pad[0x1C];
    char *displayContexts;
} ShadowState;

extern ShadowState *D_0013617C;
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern int getFrameBufferSize(void);
extern int getZBufferAddressFBP(void);
extern void iosSetDCParam(char *, int, int, int, int);

void shadowReInit(void)
{
    int width = getDrawScreenWidth();
    int height = getDrawScreenHeight();
    int i;

    for (i = 0; i < 2; i++) {
        int frame = (getFrameBufferSize() + 0x14000) >> 11;
        int depth = getZBufferAddressFBP();

        iosSetDCParam(D_0013617C->displayContexts + i * 0x190,
                      frame, depth, width, height);
    }
}
