extern struct { char pad[0x168]; float f; } gcGlobalVar;
extern int B_0018B6B8;
extern char RO_0017E118[], RO_0017E130[], RO_0017E098[];
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(void *, int);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetSelectMenuId(void *, int);
extern void SpriteMenuSetSelectSubMenuId(void *, int);
extern void controllerAlertDisable(int);
extern int *getProgressiveMode(void);
extern void graphFrameBufferReInitializeRequest(void);

static void func_00072EE8(void *menu, int *x, unsigned flags, int mode)
{
    if (flags & 1) {
        switch (mode) {
        case 0:
        {
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E118)), 0);
            controllerAlertDisable(1);
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E130)), 1);
            SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E130)));
            SpriteMenuSetSelectMenuId(menu, 0);
            *(float *)(x + 5) = gcGlobalVar.f;
            if (*getProgressiveMode() != 1) {
                *getProgressiveMode() = 1;
                graphFrameBufferReInitializeRequest();
            }
            B_0018B6B8 = 1;
            SpriteMenuSetSelectSubMenuId(menu, 1);
            *(float *)(x + 6) = gcGlobalVar.f;
            return;
        }
        case 1:
        {
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E118)), 0);
            SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
            x[4] &= -5;
            if (*getProgressiveMode() != 0) {
                *getProgressiveMode() = 0;
                graphFrameBufferReInitializeRequest();
            }
            B_0018B6B8 = 0;
            SpriteMenuSetSelectSubMenuId(menu, 0);
            return;
        }
        }
        return;
    }
    if (flags & 2) {
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E118)), 0);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
        x[4] &= -5;
        if (*getProgressiveMode() != 0) {
            *getProgressiveMode() = 0;
            graphFrameBufferReInitializeRequest();
        }
        B_0018B6B8 = 0;
        SpriteMenuSetSelectSubMenuId(menu, 0);
        return;
    }
}
