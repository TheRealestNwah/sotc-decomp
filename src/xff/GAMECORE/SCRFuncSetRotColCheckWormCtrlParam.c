extern char *getSCRDataCtrlWork(void *);
extern void setRotColCheckWormCtrlWork(void *, int);

void SCRFuncSetRotColCheckWormCtrlParam(void *actor, int v)
{
    char *w = getSCRDataCtrlWork(actor);
    if (*(int *)(w + 0x4090) == 3)
        setRotColCheckWormCtrlWork(w + 0x3D10, v);
}
