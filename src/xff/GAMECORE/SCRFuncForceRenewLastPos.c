extern void *getSCRDataCtrlWork(void *);
extern void forceRenewLastPosPerceptionWork(void *, void *);

void SCRFuncForceRenewLastPos(void *actor)
{
    forceRenewLastPosPerceptionWork(actor, (char *)getSCRDataCtrlWork(actor) + 16432);
}
