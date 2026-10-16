extern void *getSCRDataCtrlWork(void *);
extern void unsetEventLineAttr(void *, int, int);

void SCRFuncLineUnsetRoute(void *actor, int line)
{
    unsetEventLineAttr(getSCRDataCtrlWork(actor), line, 2);
}
