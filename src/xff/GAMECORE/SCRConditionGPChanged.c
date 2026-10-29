extern void *getSCRDataCtrlWork(void *);
extern int changedGPIndex(void *, char *, void *);

int SCRConditionGPChanged(void *actor)
{
    char *work = getSCRDataCtrlWork(actor);
    return changedGPIndex(actor, work, *(void **)(work + 0x4078));
}
