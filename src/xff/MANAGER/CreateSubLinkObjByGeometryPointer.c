extern char rootPtn[];
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void InitTwoWayLink(char *, int);
extern void *iosMallocAlign(void *, int, int);
extern void *GetGeometryPointerObject(char *);
extern void AddLayoutObjSubLink(void *, void *);
static int func_00099470(unsigned char *);
unsigned char *CreateSubLinkObjByGeometryPointer(char *geometry, int size)
{
    unsigned char *obj = _isysCreateObj(rootPtn, 21, 0x30, size + 0x20, 0, 16);
    if (obj) {
        unsigned char *cls;
        unsigned char *other;
        isysSetObjImmediateDeleteFunc(obj, (int)func_00099470);
        cls = obj[8] != 21 ? 0 : obj + 0x1C;
        InitTwoWayLink((char *)cls, (int)obj);
        *(void **)(cls + 0x10) = iosMallocAlign(*(void **)obj, size, 16);
        other = obj[8] != 21 ? 0 : obj + 0x1C;
        *(int *)(other + 0xC) = 0;
    }
    AddLayoutObjSubLink(GetGeometryPointerObject(geometry), obj);
    return obj;
}