extern const char RO_0017E1B0[];
extern const char RO_0017E1C8[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);
extern void SpriteMenuSetLayer(unsigned char *menu, int layer);
extern int SpriteMenuIsFadeCheckSelectLayer(unsigned char *menu);
extern int getGameClearCnt(void);
extern int GetNumOmakeItem(void);
extern int fadeChkStat(int stat);

typedef struct {
    int mode;
    int pad4;
    int ok;
    int cancel;
    int *result;
} MenuState;

static inline int getListLayer(unsigned char *menu)
{
    if (getGameClearCnt() > 0 && GetNumOmakeItem() > 0) {
        return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1B0));
    }
    return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1C8));
}

static int func_00075210(unsigned char *menu, int unused, MenuState *st)
{
    int done = 0;

    switch (st->mode) {
    case 3:
        if (st->cancel) {
            SpriteMenuSetDispFlag(menu, getListLayer(menu), 0);
            st->mode = 7;
            *st->result = 0;
            break;
        }
        if (st->ok == 0) {
            break;
        }
        SpriteMenuSetDispFlag(menu, getListLayer(menu), 1);
        SpriteMenuSetLayer(menu, getListLayer(menu));
        st->mode = 2;
        break;
    case 1:
        st->mode = 2;
        break;
    case 2:
    case 4:
    case 5:
        break;
    case 6:
        if (fadeChkStat(2) == 0) {
            break;
        }
        st->mode = 0;
        done = 1;
        break;
    case 7:
        if (SpriteMenuIsFadeCheckSelectLayer(menu)) {
            break;
        }
        st->mode = 0;
        done = 1;
        break;
    }
    return done;
}
