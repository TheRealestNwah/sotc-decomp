extern char *getSCRDataCtrlWork(void *);
extern void setObstacleWormCtrlWork(void *, int);

void SCRFuncSetObstacleWormCtrl(void *actor, int v)
{
    char *w = getSCRDataCtrlWork(actor);
    if (*(int *)(w + 0x4090) == 3)
        setObstacleWormCtrlWork(w + 0x3D10, v);
}
