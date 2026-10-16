extern void *GetSCRCharaAIWorkPtr(void *);
extern void setEventLineAttr(void *, int, int);

void SCRCerberusEventLineCut(void *actor, int line)
{
    setEventLineAttr((char *)GetSCRCharaAIWorkPtr(actor) + 0x10, line, 4);
}
