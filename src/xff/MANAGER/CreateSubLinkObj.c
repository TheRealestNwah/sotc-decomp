extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void InitTwoWayLink(char *, int);
extern void *iosMallocAlign(void *, int, int);
extern void *memcpy(void *, const void *, unsigned int);
static int func_00099470(unsigned char *);
unsigned char *CreateSubLinkObj(void *heap, int callback, void *data, int size)
{
    unsigned char *obj = _isysCreateObj(heap, 21, 0x30, size + 0x20, 0, 16);
    if (obj) {
        unsigned char *cls;
        unsigned char *other;
        isysSetObjImmediateDeleteFunc(obj, (int)func_00099470);
        cls = obj[8] != 21 ? 0 : obj + 0x1C;
        InitTwoWayLink((char *)cls, (int)obj);
        *(void **)(cls + 0x10) = iosMallocAlign(*(void **)obj, size, 16);
        other = obj[8] != 21 ? 0 : obj + 0x1C;
        *(int *)(other + 0xC) = callback;
        if (data)
            memcpy(*(void **)(other + 0x10), data, size);
    }
    return obj;
}