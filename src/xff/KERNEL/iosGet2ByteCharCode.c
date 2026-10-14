int iosGet2ByteCharCode(void *arg0)
{
    return ((*(unsigned char *)((char *)(arg0) + 1)) << 8) | (*(unsigned char *)((char *)(arg0) + 0));
}
