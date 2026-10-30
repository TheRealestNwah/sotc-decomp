extern char RO_00180950[];
extern char RO_00180960[];
extern char RO_00180970[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);

static void func_000C8CD8(unsigned char *menu, int *st, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180950), MakeStrHashValue(RO_00180960)))
            st[1] = 8;
        else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180950), MakeStrHashValue(RO_00180970)))
            st[1] = 0xD;
    } else if (flags & 2) {
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180950)), 0);
        st[1] = 0xD;
    }
}
