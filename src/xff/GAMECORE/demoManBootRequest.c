extern char *GetScriptLayoutClass(void *);
extern void SetDisplayModelNearClippingSwitch(int);

void demoManBootRequest(void *actor)
{
    char *d = *(char **)(GetScriptLayoutClass(actor) + 0x2D8);
    SetDisplayModelNearClippingSwitch(0);
    *(int *)(d + 4) = 1;
}
