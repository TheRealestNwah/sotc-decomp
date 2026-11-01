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

void CheckSelectDisp(void *menu)
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

