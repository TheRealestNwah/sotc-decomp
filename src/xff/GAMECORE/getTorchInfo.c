extern void *GetSCRCharaAIWorkPtr(void *);

int getTorchInfo(void *actor)
{
    int var_a1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    var_a1 = 0;
    if ((*(int *)((char *)(temp_v0) + 0x70)) == 9) {
        var_a1 = (*(unsigned char *)((char *)(temp_v0) + 0x94)) != 0;
    }
    return var_a1;
}
