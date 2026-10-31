extern char *GetSCRCharaAIWorkPtr(void *);
extern int _gameFlagChk(int);

static void func_0006BE58(void *obj)
{
    char *w;

    w = GetSCRCharaAIWorkPtr(obj);
    if (!_gameFlagChk(0x13F)) {
        *(int *)(w + 0x4200) = 1;
    }
}
