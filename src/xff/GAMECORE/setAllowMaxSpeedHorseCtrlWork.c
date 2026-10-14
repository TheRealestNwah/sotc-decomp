void setAllowMaxSpeedHorseCtrlWork(void *arg0, float fparg0)
{
    if (*(*(float **)((char *)(arg0) + 0x78)) < fparg0) {
        (*(float *)((char *)(arg0) + 0x40)) = fparg0;
    }
}
