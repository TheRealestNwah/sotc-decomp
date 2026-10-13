int is_LwsOrientObj(void *arg0)
{
    return (*(unsigned char *)((char *)(arg0) + 8)) == 0x16;
}
