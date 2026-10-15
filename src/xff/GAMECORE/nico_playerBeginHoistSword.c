extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern void func_00079220(void *, char *);
extern float GetWeaponRange(void);
extern void begin_nico_sight_on(char *, void *, char *, float);

void nico_playerBeginHoistSword(void *a)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    func_00079220(a, w);
    begin_nico_sight_on(w + 0x190, a, gcGlobalVar + 0x230, GetWeaponRange());
}
