extern const char RO_0017E1B0[];
extern const char RO_0017E1C8[];
extern const char RO_0017E1E0[];
extern const char RO_0017E1F0[];
extern int SeList_cancel;
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);
extern void SpriteMenuSetLayer(unsigned char *menu, int layer);
extern void SpriteMenuSetSelectMenuId(unsigned char *menu, int id);
extern char *GetSpriteMenuClass(void);
extern void OptionMenuStart(int *a, int *b);
extern void SetItemMenuDisp(unsigned char *menu);
extern void sePlaySystemSound(int se);
extern void fadeOut(int wait, int release, float t);
extern int getGameClearCnt(void);
extern int GetNumOmakeItem(void);

typedef struct {
    int state;
    int i4;
    int i8;
    int iC;
    int *flag;
} MenuState;

static inline int getListLayer(unsigned char *menu)
{
    if (getGameClearCnt() > 0 && GetNumOmakeItem() > 0) {
        return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1B0));
    }
    return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1C8));
}

#define LAYER(name) SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(name))

static void func_00074AC8(unsigned char *menu, MenuState *state, int flags, int id)
{
    char *cls = GetSpriteMenuClass();
    const char *name;

    if (flags & 1) {
        name = RO_0017E1C8;
        if (*(int *)(cls + 0xC) == LAYER(name)) {
            switch (id) {
            case 0:
                SpriteMenuSetDispFlag(menu, LAYER(name), 0);
                state->state = 3;
                state->i8 = 0;
                OptionMenuStart(&state->i8, &state->iC);
                return;
            case 2:
                state->state = 4;
                {
                const char *n2 = RO_0017E1E0;
                SpriteMenuSetDispFlag(menu, LAYER(n2), 1);
                SpriteMenuSetLayer(menu, LAYER(n2));
                }
                SpriteMenuSetSelectMenuId(menu, 1);
                return;
            }
        } else {
            name = RO_0017E1B0;
            if (*(int *)(cls + 0xC) == LAYER(name)) {
                switch (id) {
                case 0:
                    SpriteMenuSetDispFlag(menu, LAYER(name), 0);
                    state->state = 3;
                    state->i8 = 0;
                    OptionMenuStart(&state->i8, &state->iC);
                    return;
                case 1:
                    {
                    const char *n2 = RO_0017E1F0;
                    SpriteMenuSetDispFlag(menu, LAYER(n2), 1);
                    SpriteMenuSetLayer(menu, LAYER(n2));
                    }
                    state->state = 5;
                    SetItemMenuDisp(menu);
                    return;
                case 2:
                    state->state = 4;
                    {
                    const char *n2 = RO_0017E1E0;
                    SpriteMenuSetDispFlag(menu, LAYER(n2), 1);
                    SpriteMenuSetLayer(menu, LAYER(n2));
                    }
                    SpriteMenuSetSelectMenuId(menu, 1);
                    return;
                }
            }
        }
    } else if (flags & 0x202) {
        sePlaySystemSound(SeList_cancel);
        SpriteMenuSetDispFlag(menu, getListLayer(menu), 0);
        state->state = 7;
        *state->flag = 0;
    }
}

static void func_00074E78(unsigned char *menu, MenuState *state, int flags, int id)
{
    if (flags & 1) {
        switch (id) {
        case 0:
            fadeOut(0, 1, 1.0f);
            state->state = 6;
            state->i4 = 0;
            *state->flag = 1;
            break;
        case 1:
            SpriteMenuSetDispFlag(menu, getListLayer(menu), 1);
            SpriteMenuSetDispFlag(menu, LAYER(RO_0017E1E0), 0);
            SpriteMenuSetLayer(menu, getListLayer(menu));
            state->state = 2;
            break;
        }
    } else if (flags & 2) {
        SpriteMenuSetDispFlag(menu, LAYER(RO_0017E1E0), 0);
        SpriteMenuSetDispFlag(menu, getListLayer(menu), 1);
        SpriteMenuSetLayer(menu, getListLayer(menu));
        state->state = 2;
    }
}
