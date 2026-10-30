extern int *DldSysUndefSymbol;
extern int SH_ItemMenuDEFAULT[];
extern const char RO_00180910[];
extern const char RO_00180918[];
extern int getGameHardMode(void);
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetMenuIdByHash(void *menu, int name, int item);
extern void SpriteMenuSetCheckBoxByHash(void *menu, int name, int item, int on);
extern int _omakeSelectFlagChk(int);
extern void _omakeSelectFlagSet(int);
extern void _omakeSelectFlagCls(int);
extern int getSelectWeapon(void);
extern int _omakeGetFlagChk(int);
extern int SpriteMenuGetLayerNoByHash(void *menu, int name);
extern void SpriteMenuSetMenuDispFlag(void *menu, int layer, int id, int on);
extern void SpriteMenuSetPartsDefValueByHash(void *menu, int name, int value, int index);

typedef struct {
    int a;
    int hash;
    int hashHard;
    int value;
    int valueHard;
    int pad14;
    int flag;
    unsigned int weapon;
} OmakeItem;

static inline int *getItemMenu(void)
{
    return DldSysUndefSymbol != SH_ItemMenuDEFAULT ? SH_ItemMenuDEFAULT : 0;
}

static inline void updateCheckBoxes(void *menu)
{
    int *sh = getItemMenu();
    int cnt = sh[3];
    OmakeItem *it = (OmakeItem *)sh[4];
    int box = MakeStrHashValue(RO_00180918);
    int i;
    int h;

    for (i = 0; i < cnt; i++) {
        if (getGameHardMode())
            h = it[i].hashHard;
        else
            h = it[i].hash;
        if (h == MakeStrHashValue(RO_00180910))
            continue;
        SpriteMenuSetCheckBoxByHash(menu, box, h, _omakeSelectFlagChk(it[i].flag));
    }
}

void SetItemMenuDisp(void *menu)
{
    {
        int *sh = getItemMenu();
        int cnt = sh[3];
        OmakeItem *it = (OmakeItem *)sh[4];
        int box = MakeStrHashValue(RO_00180918);
        int i;
        int h;
        int menuId;
        int flag;
        int on;

        for (i = 0; i < cnt; i++) {
            if (getGameHardMode())
                h = it[i].hashHard;
            else
                h = it[i].hash;
            if (h == MakeStrHashValue(RO_00180910))
                continue;
            flag = it[i].flag;
            menuId = SpriteMenuGetMenuIdByHash(menu, box, h);
            on = _omakeGetFlagChk(flag);
            SpriteMenuSetMenuDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, box), menuId, on);
            SpriteMenuSetPartsDefValueByHash(menu, box, getGameHardMode() ? it[i].valueHard : it[i].value, i);
        }
    }
    updateCheckBoxes(menu);
}

void SelectOmakeItem(void *menu, int id)
{
    {
        int *sh = getItemMenu();
        int cnt = sh[3];
        OmakeItem *it = (OmakeItem *)sh[4];
        int box = MakeStrHashValue(RO_00180918);
        int i;
        int h;
        int flag;

        for (i = 0; i < cnt; i++) {
            if (getGameHardMode())
                h = it[i].hashHard;
            else
                h = it[i].hash;
            if (h == MakeStrHashValue(RO_00180910))
                continue;
            if (id != SpriteMenuGetMenuIdByHash(menu, box, h))
                continue;
            flag = it[i].flag;
            if (_omakeSelectFlagChk(flag)) {
                if (((it[i].weapon >> 18) & 0xFFF) != getSelectWeapon())
                    _omakeSelectFlagCls(flag);
            } else {
                _omakeSelectFlagSet(flag);
            }
        }
    }
    updateCheckBoxes(menu);
}
