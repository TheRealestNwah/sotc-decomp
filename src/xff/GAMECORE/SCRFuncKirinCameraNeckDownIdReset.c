extern void *GetLayoutClass(void *);

void SCRFuncKirinCameraNeckDownIdReset(void *actor)
{
    (*(int *)((char *)(GetLayoutClass(actor)) + 0x1AC)) = 0;
}
