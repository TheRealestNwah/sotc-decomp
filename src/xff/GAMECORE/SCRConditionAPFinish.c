extern void *getSCRDataCtrlWork(void *);
extern int getPathExFinish();

int SCRConditionAPFinish(void *actor)
{
    return getPathExFinish(((int)getSCRDataCtrlWork(actor)), 2);
}
