void Kite_StartEventCheck(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 0)) = arg1;
    (*(int *)((char *)(arg0) + 8)) = 1;
    (*(int *)((char *)(arg0) + 4)) = 0;
}
