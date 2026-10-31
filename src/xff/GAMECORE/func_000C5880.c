typedef struct {
    char pad0[0x2C];
    void (*update)(unsigned char *);
} SpriteMenuClass;

typedef struct {
    int pad0;
    int mode;
    int pad8;
    unsigned int flags;
} PauseState;

typedef struct {
    char pad0[8];
    unsigned int trig;
} PadData;

extern PadData padManagerData;
extern const char RO_00180750[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuIsFadeCheckAllLayer(unsigned char *menu);
extern void SpriteMenuSetDispFlagAll(unsigned char *menu, int flag);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);
extern SpriteMenuClass *GetSpriteMenuClass(unsigned char *menu);
extern void OptionMenuStart(int *done, int b);
extern void scrRun(void);
extern void func_000C8480(void);
extern void func_000C84F8(void);

static int func_000C5880(unsigned char *menu, PauseState *st)
{
    if (SpriteMenuIsFadeCheckAllLayer(menu))
        return 0;
    if (padManagerData.trig & 0x800)
        st->mode = 9;
    switch (st->mode) {
    case 13:
        if (SpriteMenuIsFadeCheckAllLayer(menu))
            break;
        SpriteMenuSetDispFlagAll(menu, 0);
        return 1;
    case 9:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180750)), 0);
        return 1;
    case 3:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180750)), 0);
        func_000C8480();
        return 1;
    case 4:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180750)), 0);
        func_000C84F8();
        return 1;
    case 16: {
        int done = 0;
        SpriteMenuClass *cls = GetSpriteMenuClass(menu);

        OptionMenuStart(&done, 0);
        while (!done) {
            cls->update(menu);
            scrRun();
        }
        st->mode = 2;
        break;
    }
    }
    if (st->flags & 4) {
        st->flags &= ~4;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180750)), 0);
        return 1;
    }
    return 0;
}
