extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);
extern const char RO_00180A08[];
extern const char RO_001809B8[];
extern const char RO_001809D0[];

static void func_000C8FB0(unsigned char *menu, int *state, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180A08), MakeStrHashValue(RO_001809B8))) {
            state[1] = 8;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180A08), MakeStrHashValue(RO_001809D0))) {
            state[1] = 4;
        }
    }
}
