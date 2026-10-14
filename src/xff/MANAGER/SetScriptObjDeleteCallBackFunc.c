extern char *GetScriptClass(void *);

void SetScriptObjDeleteCallBackFunc(void *actor, int func, int arg)
{
    char *s = GetScriptClass(actor);
    *(int *)(s + 0x54) = func;
    *(int *)(s + 0x58) = arg;
}
