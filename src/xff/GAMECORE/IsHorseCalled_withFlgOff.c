extern void *GetSCRCharaAIWorkPtr();

unsigned char IsHorseCalled_withFlgOff(void)
{
    unsigned char temp_v1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    temp_v1 = (*(unsigned char *)((char *)(temp_v0) + 0xD9C));
    if (temp_v1 == 1) {
        (*(unsigned char *)((char *)(temp_v0) + 0xD9C)) = 0U;
    }
    return temp_v1;
}
