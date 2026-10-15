extern char *GetScriptClass(void *);

void SetScriptObjDeleteCallBackFunc2(void *actor, int func, int arg)
{
    char *s = GetScriptClass(actor);
    *(int *)(s + 0x5C) = func;
    *(int *)(s + 0x60) = arg;
}
