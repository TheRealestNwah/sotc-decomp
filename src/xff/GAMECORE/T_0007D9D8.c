extern char *GetSCRCharaAIWorkPtr(void);
extern int SCRSetupWeaponPlayer(void *, int);

static void T_0007D9D8(void *p)
{
    char *w = GetSCRCharaAIWorkPtr() + 0x60;

    if (*(int *)(w + 0x18) == 0)
        *(int *)(w + 0x18) = SCRSetupWeaponPlayer(p, *(int *)(w + 0x10));
}
