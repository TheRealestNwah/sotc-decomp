extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncSnakeCDeflateEnd(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x5A8C)) = 1;
}
