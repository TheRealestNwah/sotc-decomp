extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);
extern const char RO_001807F0[];
extern const char RO_00180780[];
extern const char RO_00180798[];

static void func_000C8900(unsigned char *menu, int *state, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001807F0), MakeStrHashValue(RO_00180780))) {
            state[1] = 8;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001807F0), MakeStrHashValue(RO_00180798))) {
            state[1] = 4;
        }
    }
}
