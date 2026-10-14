extern void *GetScriptLayoutClass(void *);

int demoManBootChk(void *actor)
{
    return (*(int *)((char *)((*(void **)((char *)(GetScriptLayoutClass(actor)) + 0x2D8))) + 8));
}
