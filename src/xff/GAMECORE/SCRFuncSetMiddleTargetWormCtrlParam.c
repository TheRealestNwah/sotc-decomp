extern char *getSCRDataCtrlWork(void *);
extern void setMiddleTargetWormCtrlWork(void *, int);

void SCRFuncSetMiddleTargetWormCtrlParam(void *actor, int v)
{
    char *w = getSCRDataCtrlWork(actor);
    if (*(int *)(w + 0x4090) == 3)
        setMiddleTargetWormCtrlWork(w + 0x3D10, v);
}
