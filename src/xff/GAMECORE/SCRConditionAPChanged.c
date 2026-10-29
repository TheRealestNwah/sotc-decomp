extern void *getSCRDataCtrlWork(void *);
extern int changedAPIndex(void *, char *);

int SCRConditionAPChanged(void *actor)
{
    return changedAPIndex(actor, getSCRDataCtrlWork(actor));
}
