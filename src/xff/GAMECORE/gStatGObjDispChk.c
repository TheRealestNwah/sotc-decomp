int gStatGObjDispChk(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x10)) & 1;
}
