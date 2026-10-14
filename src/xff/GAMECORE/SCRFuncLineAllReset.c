extern void *getSCRDataCtrlWork(void *);
extern int allResetLineAttr();

int SCRFuncLineAllReset(void *actor)
{
    return allResetLineAttr(((int)getSCRDataCtrlWork(actor)));
}
