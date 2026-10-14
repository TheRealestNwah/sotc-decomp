extern void *GetLayoutClass(void *);

void SCRFuncKirinCameraNeckDownIdSet(void *actor)
{
    (*(int *)((char *)(GetLayoutClass(actor)) + 0x1AC)) = 0xA;
}
