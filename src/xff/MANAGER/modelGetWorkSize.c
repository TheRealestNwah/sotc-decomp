int modelGetWorkSize(void *arg0)
{
    return ((*(int *)((char *)(arg0) + 0x64)) * 0x30) + ((*(int *)((char *)(arg0) + 0x54)) << 6) + 0xA1;
}
