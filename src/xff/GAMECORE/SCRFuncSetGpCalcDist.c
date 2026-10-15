extern void *getSCRDataCtrlWork(void *);
extern void setGpCalcDist(void *work, float distance);

void SCRFuncSetGpCalcDist(void *actor, float r)
{
    setGpCalcDist(getSCRDataCtrlWork(actor), r);
}
