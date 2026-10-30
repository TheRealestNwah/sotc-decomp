extern char RO_001809F8[];
extern char RO_00180960[];
extern char RO_00180970[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);

static void func_000C8EC0(unsigned char *menu, int *st, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001809F8), MakeStrHashValue(RO_00180960))) {
            st[1] = 0xB;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001809F8), MakeStrHashValue(RO_00180970))) {
            if (st[2] == 1)
                st[1] = 0xA;
            else
                st[1] = 2;
        }
    } else if (flags & 2) {
        if (st[2] == 1)
            st[1] = 0xA;
        else
            st[1] = 2;
    }
}
