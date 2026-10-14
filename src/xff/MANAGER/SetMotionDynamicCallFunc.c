void SetMotionDynamicCallFunc(char *p, int a1, int a2)
{
    *(int *)(p + 0xCC) = a1;
    *(int *)(p + 0xD0) = a2;
}
