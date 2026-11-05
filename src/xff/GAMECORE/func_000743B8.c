typedef struct {
    int *x0;
    char pad4[0x1C];
    int *x20;
} OptRef;

typedef struct {
    char pad0[0xC];
    int state;
} Work;

extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(unsigned char *, int);
extern void SpriteSubMenuSetPadEventCallback(unsigned char *, int, void *);
extern void SpriteMenuSetLayerPriorityAllLayer(unsigned char *, int);
extern void SpriteMenuSetLayerPriority(unsigned char *, int, int);
extern void SpriteMenuSetSliderValueByHashStr(unsigned char *, const char *, const char *, int);
extern void SpriteMenuSetDispFlag(unsigned char *, int, int);
extern void SpriteMenuSetLayer(unsigned char *, int);
extern int SpriteMenuIsFadeCheckSelectLayer(unsigned char *);
extern char RO_0017E098[];
extern char RO_0017E0A8[];
extern char RO_0017E160[];
extern char RO_0017E180[];
extern OptRef D_0017ADE0;
extern void func_00073D20(void);
extern void func_00073F70(unsigned char *, void *, Work *);

static int func_000743B8(unsigned char *menu, void *arg, Work *w)
{
    int ret = 0;

    switch (w->state) {
    case 1:
        SpriteSubMenuSetPadEventCallback(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)), func_00073D20);
        SpriteMenuSetLayerPriorityAllLayer(menu, 4);
        SpriteMenuSetLayerPriority(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0A8)), 3);
        SpriteMenuSetSliderValueByHashStr(menu, RO_0017E098, RO_0017E160, *D_0017ADE0.x0);
        SpriteMenuSetSliderValueByHashStr(menu, RO_0017E098, RO_0017E180, *D_0017ADE0.x20);
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E0A8)), 1);
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)), 1);
        SpriteMenuSetLayer(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E098)));
        w->state = 2;
        break;
    case 2:
        func_00073F70(menu, arg, w);
        break;
    case 3:
        if (!SpriteMenuIsFadeCheckSelectLayer(menu)) {
            w->state = 0;
            ret = 1;
        }
        break;
    }
    return ret;
}
