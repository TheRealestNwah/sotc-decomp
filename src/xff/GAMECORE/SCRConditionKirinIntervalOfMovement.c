extern char *getSCRDataCtrlWork(void *);

int SCRConditionKirinIntervalOfMovement(void *actor, int n, int lim)
{
    return (int)*(float *)(getSCRDataCtrlWork(actor) + 0x40A4) % n < lim;
}
