extern void *GetScriptLayoutClass(void *);

int demoManChkStart(void *actor)
{
    return (*(int *)((char *)((*(void **)((char *)(GetScriptLayoutClass(actor)) + 0x2D8))) + 0x44)) != 0;
}
