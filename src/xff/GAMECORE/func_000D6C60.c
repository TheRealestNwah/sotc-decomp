extern void GAMEUTIL_reset_status_manager(void *, int);

static void func_000D6C60(char *p)
{
    *(int *)(p + 0x378) = 1;
    GAMEUTIL_reset_status_manager(p + 0x37C, 1);
}
