extern int GetSCRCharaAIWorkPtr(int);

void nico_restartWormGenealogicalNodeFromDemo(int *arg0)
{
    (*(signed char *)((char *)(((GetSCRCharaAIWorkPtr(*arg0) + 0x41B3) & ~0xF)) + 0x1298)) = 0;
}
