extern void *getSCRDataCtrlWork(void *);
extern void setEventLineAttr(void *, int, int);

void SCRFuncLineCut(void *actor, int line)
{
    setEventLineAttr(getSCRDataCtrlWork(actor), line, 4);
}
