int setAttainSpeedWormCtrlWork(void *arg0, float fparg0)
{
    if ((fparg0 >= 0.0f) && (fparg0 <= (*(float *)((char *)(arg0) + 0x58)))) {
        (*(float *)((char *)(arg0) + 0xB0)) = fparg0;
        return 1;
    }
    return 0;
}
