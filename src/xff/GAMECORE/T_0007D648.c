extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern float GetWeaponRange(void);
extern void begin_nico_sight_on(void *, void *, void *, float);
extern void func_00079220(void *, char *);
extern void func_000794E0(void *);
extern void func_00079978(void *);

static void T_0007D648(void *obj)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);

    func_00079220(obj, ai);
    begin_nico_sight_on(ai + 0x190, obj, gcGlobalVar + 0x260, GetWeaponRange());
    func_000794E0(obj);
}

static void T_0007D6A8(void *obj)
{
    char *ai = GetSCRCharaAIWorkPtr(obj);

    func_00079220(obj, ai);
    begin_nico_sight_on(ai + 0x190, obj, gcGlobalVar + 0x260, GetWeaponRange());
    func_00079978(obj);
}
