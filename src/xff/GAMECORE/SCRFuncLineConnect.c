extern void *getSCRDataCtrlWork(void *);
extern void unsetEventLineAttr(void *, int, int);

void SCRFuncLineConnect(void *actor, int line)
{
    unsetEventLineAttr(getSCRDataCtrlWork(actor), line, 4);
}
