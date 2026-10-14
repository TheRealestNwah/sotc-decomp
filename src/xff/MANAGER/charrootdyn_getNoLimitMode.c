void charrootdyn_getNoLimitMode(void *arg0, void *arg1)
{
    (*(int *)((char *)(arg0) + 0)) = 0;
    (*(int *)((char *)(arg0) + 4)) = 0;
    (*(int *)((char *)(arg0) + 8)) = (int) (*(int *)((char *)(arg1) + 0xC30));
}
