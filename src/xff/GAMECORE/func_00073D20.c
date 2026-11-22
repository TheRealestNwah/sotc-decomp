extern struct { char pad[0x168]; float f; } gcGlobalVar;
extern int B_0018B6B8;
extern char RO_0017E118[], RO_0017E098[];
extern int *D_0017ADE0[];
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(void *, int);
extern int SpriteMenuGetSelectLayer(void);
extern int SpriteMenuGetSelectSubMenuId(void *);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetSelectMenuId(void *, int);
extern void SpriteMenuSetSelectMenuMode(void *, int);
extern void SpriteMenuSetSelectSubMenuId(void *, int);
extern int *getProgressiveMode(void);
extern void graphFrameBufferReInitializeRequest(void);
extern void func_00072758();

static void func_00073D20(void *menu, int *x, unsigned flags, int mode, int value)
{
    if (flags & 1)
        return;
    if (!(flags & 0x30))
        return;
    if (SpriteMenuGetSelectLayer() != SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)))
        return;
    switch (mode) {
    case 0:
    case 8:
        if (D_0017ADE0[mode] != 0)
            *D_0017ADE0[mode] = value;
        func_00072758();
        return;
    case 3:
    {
        int **b = D_0017ADE0;
        int **p = b + 3;
        if (*p != 0)
            **p = SpriteMenuGetSelectSubMenuId(menu);
        SpriteMenuSetSelectMenuMode(menu, 0);
        if (**p == 1) {
            x[4] |= 4;
            SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E118)));
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E118)), 1);
            SpriteMenuSetSelectMenuId(menu, 1);
            return;
        }
        *(float *)(x + 5) = gcGlobalVar.f - 3.0f + 1.0f;
        if (*getProgressiveMode() != 0) {
            *getProgressiveMode() = 0;
            graphFrameBufferReInitializeRequest();
        }
        B_0018B6B8 = 0;
        SpriteMenuSetSelectSubMenuId(menu, 0);
        return;
    }
    default:
        if (D_0017ADE0[mode] != 0)
            *D_0017ADE0[mode] = SpriteMenuGetSelectSubMenuId(menu);
        return;
    }
}
