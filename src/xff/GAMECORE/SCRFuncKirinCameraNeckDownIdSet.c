extern void *GetLayoutClass();

void SCRFuncKirinCameraNeckDownIdSet(void)
{
    (*(int *)((char *)(GetLayoutClass()) + 0x1AC)) = 0xA;
}
