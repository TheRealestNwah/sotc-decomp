extern void *getSCRDataCtrlWork(void *);
extern void resetPassageWork(void *work);

void SCRFuncResetPathSystem(void *actor)
{
    resetPassageWork(getSCRDataCtrlWork(actor));
}
