extern char RO_001809F8[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);
extern void ReplayPauseScriptBegin(void);
extern void func_000C8C58(void);

static int func_000C72E0(unsigned char *menu, int *st)
{
    switch (st[1]) {
    case 0xB:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001809F8)), 0);
        return 1;
    case 2:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001809F8)), 0);
        ReplayPauseScriptBegin();
        return 1;
    case 0xA:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001809F8)), 0);
        func_000C8C58();
        return 1;
    default:
        if (st[3] & 0x10) {
            st[3] &= ~0x10;
            SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001809F8)), 0);
            return 1;
        }
        return 0;
    }
}
