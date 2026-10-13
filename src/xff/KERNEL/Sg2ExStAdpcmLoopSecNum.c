int Sg2ExStAdpcmLoopSecNum(void *arg0, int *arg1, int *arg2)
{
    *arg1 = (*(int *)((char *)(arg0) + 0x38));
    *arg2 = (*(int *)((char *)(arg0) + 0x3C));
    return 0;
}
