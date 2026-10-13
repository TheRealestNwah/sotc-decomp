extern void *GetSCRCharaAIWorkPtr();

void SCRFuncSnakeCDeflateEnd(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x5A8C)) = 1;
}
