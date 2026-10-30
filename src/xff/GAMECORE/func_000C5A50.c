extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern void timeAttackPauseScriptBegin(void);
extern void func_000C8570(void);
extern const char RO_001807E0[];

static int func_000C5A50(unsigned char *menu, int *state)
{
    switch (state[1]) {
    case 0xB:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001807E0)), 0);
        return 1;
    case 2:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001807E0)), 0);
        timeAttackPauseScriptBegin();
        return 1;
    case 0xA:
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001807E0)), 0);
        func_000C8570();
        return 1;
    }
    if (state[3] & 0x10) {
        state[3] &= ~0x10;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_001807E0)), 0);
        return 1;
    }
    return 0;
}
