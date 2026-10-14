extern void *getSCRDataCtrlWork(void *);
extern int getPathStatus();

int SCRConditionPathStatus(void *actor)
{
    return getPathStatus(((int)getSCRDataCtrlWork(actor)));
}
