typedef struct {
    int state;
    int pad4;
    int sel;
    int done;
    char pad10[0x1C - 0x10];
    int button;
} PauseWork;

extern char gcGlobalVar[];
extern char rootPtn[];
extern int B_0019FCF0;

extern int SpriteMenuGetPadEvent(void);
extern void PauseMenuStart(int *, int *);
extern int SpriteMenuIsFadeCheckSelectLayer(void *);
extern void SpriteMenuSetDispFlagAll(void *, int);
extern int getGameClearCnt(void);
extern int GetNumOmakeItem(void);
extern void st_pausemenu_load_omake_chara(int *);
extern void *gcCreateScriptObj(void *, int *, void *, int, int, int, const char *);
extern void *SCRGetFirstObj(void *);
extern int getCurWeapon(void *);
extern int chkPossessWeapon(int);
extern void SCRPlayerGetWeapon(int);

static int func_000CF8E8(void *menu, void *unused, PauseWork *w)
{
    int ret = 0;
    int pad = SpriteMenuGetPadEvent();

    switch (w->state) {
    case 0:
        break;
    case 1:
        PauseMenuStart(&w->done, &w->sel);
        w->state = 2;
        break;
    case 2:
        if (SpriteMenuIsFadeCheckSelectLayer(menu))
            break;
        w->state = 3;
        break;
    case 3:
        if (pad & 0x80)
            w->button = 1;
        else if (pad & 0x100)
            w->button = 2;
        if (w->done == 0)
            break;
        SpriteMenuSetDispFlagAll(menu, 0);
        if (getGameClearCnt() > 0 && GetNumOmakeItem() > 0) {
            B_0019FCF0 = 0;
            gcCreateScriptObj(st_pausemenu_load_omake_chara, &B_0019FCF0, rootPtn, 0x1000, 0, 8,
                              "st_load_omake");
            w->state = 4;
        } else {
            w->state = 5;
        }
        break;
    case 4:
        if (B_0019FCF0 == 0)
            break;
        if (!chkPossessWeapon(getCurWeapon(SCRGetFirstObj(gcGlobalVar + 0x2B0))))
            SCRPlayerGetWeapon(1);
    case 5:
        w->state = 0;
        ret = 1;
        break;
    }
    return ret;
}
