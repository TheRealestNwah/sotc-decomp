extern char *GetScriptLayoutClass(void *);
void demoManStart(void *actor, int value)
{
    char *d=*(char **)(GetScriptLayoutClass(actor) + 0x2D8);
    *(int *)(d + 0x48)=value;
    *(int *)(d + 0xC)=1;
    *(int *)(d + 0x38)=0;
    *(int *)(d + 0x3C)=0;
    *(int *)(d + 0x44)=0;
    *(int *)(d + 0x34)=0;
}
