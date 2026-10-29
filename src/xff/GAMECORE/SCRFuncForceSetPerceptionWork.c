extern void *getSCRDataCtrlWork(void *);
extern void forceSetPerceptionWork(void *, void *);

void SCRFuncForceSetPerceptionWork(void *actor)
{
    forceSetPerceptionWork(actor, (char *)getSCRDataCtrlWork(actor) + 16432);
}
