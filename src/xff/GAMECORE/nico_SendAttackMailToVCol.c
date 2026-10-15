extern char *GetCharacterClass(void *);
extern int getCurWeapon(void *);
extern void ConvertGeometryPointerZNormalMode(void *, char *);
extern void *GetGeometryPointerObject(void *);
extern int getSelectWeapon(void);
extern void SendCharaAttackMsg(void *, void *, void *, int, float);

void nico_SendAttackMailToVCol(void *o)
{
    char g[0x40] __attribute__((aligned(16)));
    void *t;
    char *c = GetCharacterClass(o);
    if (getCurWeapon(o) == 9)
        return;
    if (*(int *)(c + 0xF3C) != 0) {
        ConvertGeometryPointerZNormalMode(g, c + 0xEF0);
        t = GetGeometryPointerObject(g);
        SendCharaAttackMsg(o, t, g, 0, getSelectWeapon());
    }
}
