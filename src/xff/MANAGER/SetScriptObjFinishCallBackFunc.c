extern char *GetScriptClass(void *);

void SetScriptObjFinishCallBackFunc(void *actor, int func, int arg)
{
    char *s = GetScriptClass(actor);
    *(int *)(s + 0x4C) = func;
    *(int *)(s + 0x50) = arg;
}
