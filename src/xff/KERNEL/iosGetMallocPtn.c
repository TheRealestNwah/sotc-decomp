int iosGetMallocPtn(void *arg0)
{
    void *temp_v1;

    temp_v1 = (*(void **)((char *)(arg0) + -4));
    return (((*(unsigned char *)((char *)(temp_v1) + 0xB)) << 0x10) | ((*(unsigned char *)((char *)(temp_v1) + 7)) << 8) | (*(unsigned char *)((char *)(temp_v1) + 3))) * 4;
}
