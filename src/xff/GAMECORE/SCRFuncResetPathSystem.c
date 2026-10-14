extern void *getSCRDataCtrlWork(void *);
extern int resetPassageWork();

int SCRFuncResetPathSystem(void *actor)
{
    return resetPassageWork(((int)getSCRDataCtrlWork(actor)));
}
