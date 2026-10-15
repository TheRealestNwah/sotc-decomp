extern void *getSCRDataCtrlWork(void *);
extern void setCreateTempAttain(void *work, int enabled);

void SCRFuncSetCreateTempAttain(void *actor, int enabled)
{
    setCreateTempAttain(getSCRDataCtrlWork(actor), enabled);
}
