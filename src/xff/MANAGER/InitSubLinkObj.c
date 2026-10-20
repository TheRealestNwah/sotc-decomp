extern void InitTwoWayLink(char *, int);
extern void *iosMallocAlign(void *, int, int);
extern void *memcpy(void *, const void *, unsigned int);
void InitSubLinkObj(unsigned char *obj, int callback, void *data, int size)
{
    unsigned char *cls = obj[8] != 21 ? 0 : obj + 0x1C;
    unsigned char *other;
    InitTwoWayLink((char *)cls, (int)obj);
    *(void **)(cls + 0x10) = iosMallocAlign(*(void **)obj, size, 16);
    other = obj[8] != 21 ? 0 : obj + 0x1C;
    *(int *)(other + 0xC) = callback;
    if (data)
        memcpy(*(void **)(other + 0x10), data, size);
}