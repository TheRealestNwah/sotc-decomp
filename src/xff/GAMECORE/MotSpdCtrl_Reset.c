void MotSpdCtrl_Reset(char *p)
{
    *(char *)(p + 0x10) = 0;
    *(int *)(p + 0x0) = 0;
    *(char *)(p + 0x11) = 0;
}
