extern void *GetLayoutClass();

void SCRFuncKirinCameraNeckDownIdReset(void)
{
    (*(int *)((char *)(GetLayoutClass()) + 0x1AC)) = 0;
}
