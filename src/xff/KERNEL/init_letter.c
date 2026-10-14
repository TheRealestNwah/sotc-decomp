void init_letter(void *arg0, int *arg1, int *arg2)
{
    *arg1 = 0;
    *arg2 = 0;
    (*(int *)((char *)(arg0) + 0x20)) = 1;
}
