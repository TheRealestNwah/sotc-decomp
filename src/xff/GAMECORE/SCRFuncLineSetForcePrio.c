extern void *getSCRDataCtrlWork(void *);
extern void setEventLinePrio(void *, int, int);

void SCRFuncLineSetForcePrio(void *actor, int line)
{
    setEventLinePrio(getSCRDataCtrlWork(actor), line, 0x81);
}
