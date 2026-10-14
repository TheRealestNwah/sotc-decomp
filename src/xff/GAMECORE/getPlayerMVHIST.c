extern int GetSCRCharaAIWorkPtr();

int getPlayerMVHIST(void)
{
    return GetSCRCharaAIWorkPtr() + 0xE00;
}
