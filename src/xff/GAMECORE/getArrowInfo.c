extern void *GetSCRCharaAIWorkPtr(int);
extern void *GetScriptCharacterClass(void *);

void getArrowInfo(int arg0, int arg1)
{
    if ((arg0 != 0) && ((*(int *)((char *)(GetScriptCharacterClass((void *)arg0)) + 0x1200)) != 0)) {
        (*(int *)((char *)(GetSCRCharaAIWorkPtr(arg0)) + 0x20)) = arg1;
    }
}
