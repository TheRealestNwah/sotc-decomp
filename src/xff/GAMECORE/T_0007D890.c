extern char *GetSCRCharaAIWorkPtr(void);
extern void *GetGeometryPointerObject(void *);
extern int getSelectWeapon(void);
extern void SendCharaAttackMsg(void *, void *, void *, int, float);

static void T_0007D890(void *p)
{
    char *w = GetSCRCharaAIWorkPtr() + 0xA0;
    void *g;

    *(int *)(w + 0x40) = 1;
    g = GetGeometryPointerObject(w);
    SendCharaAttackMsg(p, g, w, 0, (float)getSelectWeapon());
    *(int *)(w + 0x40) = 0;
}
