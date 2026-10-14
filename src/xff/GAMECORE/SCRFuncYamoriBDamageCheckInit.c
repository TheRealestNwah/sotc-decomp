extern void *GetSCRCharaAIWorkPtr(void);

void SCRFuncYamoriBDamageCheckInit(void)
{
    float *slot;
    int count;

    slot = (float *)((char *)GetSCRCharaAIWorkPtr() + 0x41BC);
    count = 3;
    do {
        count -= 1;
        *slot = -1.0f;
        slot -= 1;
    } while (count >= 0);
}
