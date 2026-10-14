extern void *getSCRDataCtrlWork(void *);

void SCRFuncSetAngryValue(void *actor, float fparg0)
{
    (*(float *)((char *)(getSCRDataCtrlWork(actor)) + 0x40F8)) = fparg0;
}
