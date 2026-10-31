extern char *GetScriptLayoutClass(void *);

static int func_000EBE78(void *obj)
{
    char *c = GetScriptLayoutClass(obj);

    if (c == 0)
        return 1;
    return *(int *)(c + 0x2D0) != 0;
}
