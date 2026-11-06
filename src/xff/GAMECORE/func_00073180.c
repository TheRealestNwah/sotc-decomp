extern char gcGlobalVar[];
extern int B_0018B6B8;
extern char RO_0017E130[], RO_0017E098[];
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(void *, int);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetSelectSubMenuId(void *, int);
extern void controllerAlertDisable(int);
extern int *getProgressiveMode(void);
extern void graphFrameBufferReInitializeRequest(void);

static void func_00073180(void *menu, int *x, unsigned flags, int mode)
{
    if (flags & 1) {
        if (mode != 0) {
            if (mode == 1) {
                controllerAlertDisable(0);
                SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E130)), 0);
                SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
                x[4] &= -5;
            }
        } else {
            controllerAlertDisable(0);
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E130)), 0);
            SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
            x[4] &= -5;
            *(float *)(x + 5) = *(float *)(gcGlobalVar + 0x168) - 3.0f + 1.0f;
            if (*getProgressiveMode() != 0) {
                *getProgressiveMode() = 0;
                graphFrameBufferReInitializeRequest();
            }
            B_0018B6B8 = 0;
            SpriteMenuSetSelectSubMenuId(menu, 0);
        }
        return;
    }
    if (flags & 2) {
        controllerAlertDisable(0);
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E130)), 0);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
        x[4] &= -5;
        *(float *)(x + 5) = *(float *)(gcGlobalVar + 0x168) - 3.0f + 1.0f;
        if (*getProgressiveMode() != 0) {
            *getProgressiveMode() = 0;
            graphFrameBufferReInitializeRequest();
        }
        B_0018B6B8 = 0;
        SpriteMenuSetSelectSubMenuId(menu, 0);
        return;
    }
}
