extern const char RO_0017E1B0[];
extern const char RO_0017E1C8[];
extern const char RO_0017E1F0[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);
extern void SpriteMenuSetLayer(unsigned char *menu, int layer);
extern int getGameClearCnt(void);
extern int GetNumOmakeItem(void);
extern void SelectOmakeItem(void *menu, int id);

static inline int getListLayer(unsigned char *menu)
{
    if (getGameClearCnt() > 0 && GetNumOmakeItem() > 0) {
        return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1B0));
    }
    return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1C8));
}

static void func_000750B8(unsigned char *menu, int *state, int flags, int id)
{
    if (flags & 1) {
        SelectOmakeItem(menu, id);
        return;
    }
    if (flags & 2) {
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1F0)), 0);
        SpriteMenuSetDispFlag(menu, getListLayer(menu), 1);
        SpriteMenuSetLayer(menu, getListLayer(menu));
        *state = 2;
    }
}
