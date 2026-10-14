extern void *getSCRDataCtrlWork(void *);
extern int getPathExFinish();

int SCRConditionGPFinish(void *actor)
{
    return getPathExFinish(((int)getSCRDataCtrlWork(actor)), 5);
}
