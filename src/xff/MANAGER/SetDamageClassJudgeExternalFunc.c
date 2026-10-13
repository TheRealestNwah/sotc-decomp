int SetDamageClassJudgeExternalFunc(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0x94)) = arg1;
    return 1;
}
