int Sg2ExStAdpcmGetTargetLsn(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x2D8)) + ((unsigned int) (*(unsigned int *)((char *)(arg0) + 0x248)) >> 0xB);
}
