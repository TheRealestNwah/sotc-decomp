extern void *memcpy(void *, const void *, unsigned int);

void SetSubLinkObjDeleteFuncInfo(unsigned char *p, int func, void *data, int size)
{
    unsigned char *s = p[8] != 0x15 ? 0 : p + 0x1C;
    *(int *)(s + 0xC) = func;
    if (data != 0)
        memcpy(*(void **)(s + 0x10), data, size);
}
