extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetMenuIdByHash(unsigned char *menu, int name, int item);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern const char RO_00180720[];
extern const char RO_00180730[];
extern const char RO_00180740[];

static void func_000C8628(unsigned char *menu, int *state, int flags, int id)
{
    if (flags & 1) {
        if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180720), MakeStrHashValue(RO_00180730))) {
            state[1] = 8;
        } else if (id == SpriteMenuGetMenuIdByHash(menu, MakeStrHashValue(RO_00180720), MakeStrHashValue(RO_00180740))) {
            state[1] = 0xD;
        }
    } else if (flags & 2) {
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180720)), 0);
        state[1] = 0xD;
    }
}
