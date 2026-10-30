extern char RO_001809E8[];
extern char RO_00180960[];
extern char RO_00180970[];
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);

static void func_000C8DE0(unsigned char *menu, int *st, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001809E8), MakeStrHashValue(RO_00180960)))
            st[1] = 8;
        else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001809E8), MakeStrHashValue(RO_00180970)))
            st[1] = 2;
    } else if (flags & 2) {
        st[1] = 2;
    }
}
