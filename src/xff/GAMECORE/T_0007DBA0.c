extern char *GetSCRCharaAIWorkPtr(void *);
extern void setSelectWeapon(int w);
extern void func_0007A8F0(void *, int);
extern void *nico_GetPlayerCharacterRidingHorseObject(void *actor);
extern void setHorseForceScriptKey(void *actor, int *key);
extern int *ScriptCtrlDef_SCRHorseKicked;

static void T_0007DBA0(void *obj)
{
    char *w = GetSCRCharaAIWorkPtr(obj);
    int old = *(int *)(w + 0x70);
    *(int *)(w + 0x7C) = 1;
    *(int *)(w + 0x70) = 1;
    setSelectWeapon(1);
    func_0007A8F0(obj, old);
}

static void T_0007DBF0(void *obj)
{
    char *w = GetSCRCharaAIWorkPtr(obj);
    int old = *(int *)(w + 0x70);
    *(int *)(w + 0x7C) = 8;
    *(int *)(w + 0x70) = 8;
    setSelectWeapon(8);
    func_0007A8F0(obj, old);
}

static void T_0007DC40(void *actor)
{
    void *horse = nico_GetPlayerCharacterRidingHorseObject(actor);
    if (horse)
        setHorseForceScriptKey(horse, ScriptCtrlDef_SCRHorseKicked);
}
