extern void *getSCRDataCtrlWork(void *);
extern int setGpCalcDist(int, float);

int SCRFuncSetGpCalcDist(void *actor, float r)
{
    return setGpCalcDist(((int)getSCRDataCtrlWork(actor)), r);
}
