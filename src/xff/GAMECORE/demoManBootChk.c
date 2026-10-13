extern void *GetScriptLayoutClass();

int demoManBootChk(void)
{
    return (*(int *)((char *)((*(void **)((char *)(GetScriptLayoutClass()) + 0x2D8))) + 8));
}
