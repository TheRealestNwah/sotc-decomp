extern void *getSCRDataCtrlWork(void *);
extern int getPathExFinish();

int SCRConditionPPFinish(void *actor)
{
    return getPathExFinish(((int)getSCRDataCtrlWork(actor)), 9);
}
