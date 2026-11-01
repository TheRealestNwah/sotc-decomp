extern char *GetSCRCharaAIWorkPtr(void);
extern void CopyGeometryPointer(void *, void *);
extern void *GetGeometryPointerObject(void *);
extern void setBossAbsoluteDeath(void *);
extern int getSelectWeapon(void);
extern void SendCharaAttackMsg(void *, void *, void *, int, float);

static void T_0007D900(void *p)
{
    char *w = GetSCRCharaAIWorkPtr();
    char *b = w + 0xF0;
    void *g;

    w += 0xA0;
    CopyGeometryPointer(w, b);
    setBossAbsoluteDeath(GetGeometryPointerObject(b));
    *(int *)(w + 0x40) = 1;
    g = GetGeometryPointerObject(w);
    SendCharaAttackMsg(p, g, w, 0, (float)getSelectWeapon());
    *(int *)(w + 0x40) = 0;
}
