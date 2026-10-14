extern void *getSCRDataCtrlWork(void *);

void SCRFuncParentRelateInit(void *actor)
{
    int *w = (int *)(((char *)getSCRDataCtrlWork(actor)) + 0x40D8);

    w[0] = 0;
    w[1] = 0;
}
