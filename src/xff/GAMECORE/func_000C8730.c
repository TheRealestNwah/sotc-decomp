extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);
extern const char RO_001807C8[];
extern const char RO_00180730[];
extern const char RO_00180740[];

static void func_000C8730(unsigned char *menu, int *state, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001807C8), MakeStrHashValue(RO_00180730))) {
            state[1] = 8;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_001807C8), MakeStrHashValue(RO_00180740))) {
            state[1] = 2;
        }
    } else if (flags & 2) {
        state[1] = 2;
    }
}
