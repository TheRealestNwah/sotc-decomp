extern void *getSCRDataCtrlWork(void *);
extern void updateUserPathWorkEx(void *, void *, int);

void SCRFuncUpdatePathSystem(void *actor)
{
    char *work;

    work = getSCRDataCtrlWork(actor);
    updateUserPathWorkEx(actor, work, *(int *)(work + 0x4078));
}
