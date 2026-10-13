void isysObjDeleteUnLock(void *arg0)
{
    unsigned int temp_a1;

    temp_a1 = (*(unsigned int *)((char *)(arg0) + 8));
    (*(unsigned int *)((char *)(arg0) + 8)) = (unsigned int) ((temp_a1 & 0x1FFFF) | (((temp_a1 >> 0x11) - 1) << 0x11));
}
