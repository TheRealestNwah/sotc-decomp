extern void *GetSCRCharaAIWorkPtr();

int getTorchInfo(void)
{
    int var_a1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr();
    var_a1 = 0;
    if ((*(int *)((char *)(temp_v0) + 0x70)) == 9) {
        var_a1 = (*(unsigned char *)((char *)(temp_v0) + 0x94)) != 0;
    }
    return var_a1;
}
