/* Pause menu: the sprite-menu script behind the in-game pause screen, its
 * list, quit-confirm and extras sub-layers. */

typedef struct { int pad0[2]; int *result; int padC; } SpriteParam;

typedef struct {
    char pad0[0xC];
    int layer; /* the layer that has the cursor */
    char pad10[0x18];
    void (*exec)(unsigned char *, float, int, void (*)(void), void *);
    void (*draw)(unsigned char *);
} SpriteMenu;

typedef struct { char pad[0x170]; float speed; } GcGlobal;

/* State shared by the pause menu's pad callbacks and its update loop. */
typedef struct {
    int state;   /* 1 opening, 2 list, 3 option menu, 4 quit confirm, 5 extras, 6 quitting, 7 closing */
    int input;   /* passed to the sprite menu as its input switch */
    int ready;   /* cleared while the option menu runs, set by it when it ends */
    int cancel;  /* set by the option menu when it was cancelled */
    int *result; /* 1 if the player quit, 0 if the menu was closed */
} PauseMenu;

extern const char RO_0017E1B0[];
extern const char RO_0017E1C8[];
extern const char RO_0017E1E0[];
extern const char RO_0017E1F0[];
extern int SeList_cancel;
extern GcGlobal gcGlobalVar;

extern unsigned char *isysGetThisSubThread(void);
extern SpriteMenu *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern void SpriteMenuSetDispFlag(unsigned char *menu, int layer, int flag);
extern void SpriteMenuSetLayer(unsigned char *menu, int layer);
extern void SpriteMenuSetSelectMenuId(unsigned char *menu, int id);
extern int SpriteMenuIsFadeCheckSelectLayer(unsigned char *menu);
extern void SetItemMenuDisp(unsigned char *menu);
extern void SelectOmakeItem(void *menu, int id);
extern void sePlaySystemSound(int se);
extern void fadeOut(int wait, int release, float t);
extern int fadeChkStat(int stat);
extern int getGameClearCnt(void);
extern int GetNumOmakeItem(void);
extern void scrRun(void);
static void func_000755C8(unsigned char *menu, PauseMenu *state, int flags, int id);
extern void OptionMenuStart(int *ready, int *cancel);

/* The main list layer: the one with the extras entry once the game has been
 * cleared and an extra is unlocked, the plain one otherwise. */
static inline int getListLayer(unsigned char *menu)
{
    if (getGameClearCnt() > 0 && GetNumOmakeItem() > 0) {
        return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1B0));
    }
    return SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1C8));
}

#define LAYER(name) SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(name))

/* Pad callback of the main list. */
static void func_00074AC8(unsigned char *menu, PauseMenu *state, int flags, int id)
{
    SpriteMenu *cls = GetSpriteMenuClass(menu);
    const char *name;

    if (flags & 1) {
        name = RO_0017E1C8;
        if (cls->layer == LAYER(name)) {
            switch (id) {
            case 0:
                SpriteMenuSetDispFlag(menu, LAYER(name), 0);
                state->state = 3;
                state->ready = 0;
                OptionMenuStart(&state->ready, &state->cancel);
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
            if (cls->layer == LAYER(name)) {
                switch (id) {
                case 0:
                    SpriteMenuSetDispFlag(menu, LAYER(name), 0);
                    state->state = 3;
                    state->ready = 0;
                    OptionMenuStart(&state->ready, &state->cancel);
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
        *state->result = 0;
    }
}

/* Pad callback of the quit confirmation. */
static void func_00074E78(unsigned char *menu, PauseMenu *state, int flags, int id)
{
    if (flags & 1) {
        switch (id) {
        case 0:
            fadeOut(0, 1, 1.0f);
            state->state = 6;
            state->input = 0;
            *state->result = 1;
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

/* Pad callback of the extras list. */
static void func_000750B8(unsigned char *menu, PauseMenu *state, int flags, int id)
{
    if (flags & 1) {
        SelectOmakeItem(menu, id);
        return;
    }
    if (flags & 2) {
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_0017E1F0)), 0);
        SpriteMenuSetDispFlag(menu, getListLayer(menu), 1);
        SpriteMenuSetLayer(menu, getListLayer(menu));
        state->state = 2;
    }
}

/* Advances the pause menu by one frame; returns 1 once it has closed. */
static int func_00075210(unsigned char *menu, SpriteMenu *cls, PauseMenu *st)
{
    int done = 0;

    switch (st->state) {
    case 3:
        if (st->cancel) {
            SpriteMenuSetDispFlag(menu, getListLayer(menu), 0);
            st->state = 7;
            *st->result = 0;
            break;
        }
        if (st->ready == 0) {
            break;
        }
        SpriteMenuSetDispFlag(menu, getListLayer(menu), 1);
        SpriteMenuSetLayer(menu, getListLayer(menu));
        st->state = 2;
        break;
    case 1:
        st->state = 2;
        break;
    case 2:
    case 4:
    case 5:
        break;
    case 6:
        if (fadeChkStat(2) == 0) {
            break;
        }
        st->state = 0;
        done = 1;
        break;
    case 7:
        if (SpriteMenuIsFadeCheckSelectLayer(menu)) {
            break;
        }
        st->state = 0;
        done = 1;
        break;
    }
    return done;
}

void pauseMenuScript(SpriteParam *parameters)
{
    PauseMenu pm;
    SpriteParam local;
    unsigned char *thread;
    SpriteMenu *menu;

    thread = isysGetThisSubThread();
    menu = GetSpriteMenuClass(thread);
    ScrSpriteParamSetup(&local, parameters);
    SpriteMenuSetDispFlag(thread, getListLayer(thread), 1);
    SpriteMenuSetLayer(thread, getListLayer(thread));
    pm.ready = 1;
    pm.state = 1;
    pm.input = 1;
    pm.cancel = 0;
    pm.result = local.result;
    while (!func_00075210(thread, menu, &pm)) {
        menu->exec(thread, gcGlobalVar.speed, pm.ready ? pm.input : 0, (void (*)(void))func_000755C8, &pm);
        menu->draw(thread);
        scrRun();
    }
    ScrSpriteParamEnd(&local, 1);
}

/* Pad callback of the whole menu: passes the pad to the current layer's. */
static void func_000755C8(unsigned char *menu, PauseMenu *state, int flags, int id)
{
    switch (state->state) {
    case 2:
        func_00074AC8(menu, state, flags, id);
        return;
    case 4:
        func_00074E78(menu, state, flags, id);
        return;
    case 5:
        func_000750B8(menu, state, flags, id);
        break;
    }
}
