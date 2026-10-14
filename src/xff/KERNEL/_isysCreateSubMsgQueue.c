void _isysCreateSubMsgQueue(char *p, int a1, int a2, int a3)
{
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = a2;
    *(int *)(p + 0x8) = a3;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
}
