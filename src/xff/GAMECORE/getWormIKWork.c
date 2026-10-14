extern int GetSCRCharaAIWorkPtr();

int getWormIKWork(void)
{
    return (GetSCRCharaAIWorkPtr() + 0x41B3) & ~0xF;
}
