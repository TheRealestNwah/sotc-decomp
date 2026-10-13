extern void *GetScriptLayoutClass();

int demoManChkStart(void)
{
    return (*(int *)((char *)((*(void **)((char *)(GetScriptLayoutClass()) + 0x2D8))) + 0x44)) != 0;
}
