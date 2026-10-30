extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);
extern const char RO_00180750[];
extern const char RO_00180768[];
extern const char RO_00180780[];
extern const char RO_00180798[];
extern const char RO_001807B8[];

static void func_000C5750(unsigned char *menu, int *state, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180750), MakeStrHashValue(RO_00180768))) {
            state[1] = 9;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180750), MakeStrHashValue(RO_00180780))) {
            state[1] = 3;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180750), MakeStrHashValue(RO_00180798))) {
            state[1] = 4;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180750), MakeStrHashValue(RO_001807B8))) {
            state[1] = 0x10;
        }
    } else if (flags & 2) {
        state[1] = 9;
    }
}
