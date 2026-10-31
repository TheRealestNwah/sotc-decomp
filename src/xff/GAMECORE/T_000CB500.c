extern char *GetSCRCharaAIWorkPtr(void);
extern int SkelFocusDef_BOSS_HEAD;
extern void func_000C9DA0(void *, int, int);

static void T_000CB500(void *p)
{
    char *w = GetSCRCharaAIWorkPtr();

    func_000C9DA0(p, *(int *)(*(char **)(w + 0x408C) + 0x134), SkelFocusDef_BOSS_HEAD);
}
