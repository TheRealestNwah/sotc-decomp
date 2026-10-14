extern void *GetScriptCharacterClass(void *);

int CheckSCRCharaAIWorkPtr(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (arg0 != 0) {
        var_v0 = (*(int *)((char *)(GetScriptCharacterClass((void *)arg0)) + 0x1200));
    }
    return var_v0;
}
