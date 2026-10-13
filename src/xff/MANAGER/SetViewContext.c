void SetViewContext(void *arg0, int arg1, int arg2, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4)
{
    (*(float *)((char *)(arg0) + 0x30)) = fparg4;
    (*(float *)((char *)(arg0) + 0xC)) = fparg0;
    (*(float *)((char *)(arg0) + 0x24)) = fparg1;
    (*(float *)((char *)(arg0) + 0x28)) = fparg2;
    (*(float *)((char *)(arg0) + 0x2C)) = fparg3;
    (*(int *)((char *)(arg0) + 0)) = arg1;
    (*(int *)((char *)(arg0) + 4)) = arg2;
    (*(float *)((char *)(arg0) + 8)) = (float) ((float) arg1 / (float) arg2);
}
