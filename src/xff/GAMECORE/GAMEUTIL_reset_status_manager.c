void GAMEUTIL_reset_status_manager(char *p, int a1)
{
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x8) = a1;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = a1;
}
