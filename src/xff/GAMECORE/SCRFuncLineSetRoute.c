extern void *getSCRDataCtrlWork(void *);
extern void setEventLineAttr(void *, int, int);

void SCRFuncLineSetRoute(void *actor, int line)
{
    setEventLineAttr(getSCRDataCtrlWork(actor), line, 2);
}
