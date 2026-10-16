extern void *getSCRDataCtrlWork(void *);
extern int changedGPIndex(void *, void *, int);

int SCRConditionGPChanged(void *actor)
{
    char *work;

    work = getSCRDataCtrlWork(actor);
    return changedGPIndex(actor, work, *(int *)(work + 0x4078));
}
