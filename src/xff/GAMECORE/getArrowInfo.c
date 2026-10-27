extern void *GetSCRCharaAIWorkPtr(void *);
extern void *GetScriptCharacterClass(void *);

void getArrowInfo(void *arg0, int arg1)
{
    if ((arg0 != 0) && ((*(void **)((char *)(GetScriptCharacterClass(arg0)) + 0x1200)) != 0)) {
        (*(int *)((char *)(GetSCRCharaAIWorkPtr(arg0)) + 0x20)) = arg1;
    }
}
