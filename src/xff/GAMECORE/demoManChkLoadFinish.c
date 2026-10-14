extern char *GetScriptLayoutClass(void *);
int demoManChkLoadFinish(void *actor)
{
    int *d=*(int **)(GetScriptLayoutClass(actor) + 0x2D8);
    if (d[0x4C/4] < d[0x50/4] - 1) return 1;
    return d[0] == 6;
}
