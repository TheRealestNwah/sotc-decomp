extern void *getSCRDataCtrlWork(void *);
extern void allResetLineAttr(char *);

void SCRFuncLineAllReset(void *actor)
{
    allResetLineAttr(getSCRDataCtrlWork(actor));
}
