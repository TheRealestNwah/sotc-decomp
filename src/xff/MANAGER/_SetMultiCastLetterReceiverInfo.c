extern void *memcpy(void *, const void *, unsigned int);

void _SetMultiCastLetterReceiverInfo(char *p, int a, void *src, unsigned int n)
{
    *(int *)p = a;
    memcpy(p + 0x10, src, n);
}
