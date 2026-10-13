void shadowModelReInit(void *arg0)
{
    *(*(long **)((char *)(arg0) + 0x1C)) = ((int) (*(int *)((char *)(arg0) + 0x14)) >> 4) | 0x30000000 | ((long) (*(unsigned int *)((char *)(arg0) + 0x10)) << 0x20);
}
