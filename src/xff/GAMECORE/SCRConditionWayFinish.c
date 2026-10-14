extern void *getSCRDataCtrlWork(void *);
extern int getWayFinish();

int SCRConditionWayFinish(void *actor)
{
    return getWayFinish(((int)getSCRDataCtrlWork(actor)));
}
