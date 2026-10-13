void setAllowMaxSpeedFastLegCtrlWork(void *arg0, float fparg0)
{
    if ((*(float *)((char *)(arg0) + 0x7C)) < fparg0) {
        (*(float *)((char *)(arg0) + 0x50)) = fparg0;
    }
}
