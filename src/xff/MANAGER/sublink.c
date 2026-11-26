typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
typedef struct {
    Link link;
    int unk8;
    void (*callback)(unsigned char *, int);
    int arg;
} SubLink;
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void InitTwoWayLink(char *, int);
extern void *iosMallocAlign(void *, int, int);
extern void *memcpy(void *, const void *, unsigned int);
static int func_00099470(unsigned char *);
extern char rootPtn[];
extern void *GetGeometryPointerObject(char *);
extern void AddLayoutObjSubLink(void *, void *);

static inline SubLink *getSubLink(unsigned char *p)
{
    if (p[0x8] != 0x15) {
        return 0;
    }
    return (SubLink *)(p + 0x1C);
}

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

void SetSubLinkObjDeleteFuncInfo(unsigned char *p, int func, void *data, int size)
{
    unsigned char *s = p[8] != 0x15 ? 0 : p + 0x1C;
    *(int *)(s + 0xC) = func;
    if (data != 0)
        memcpy(*(void **)(s + 0x10), data, size);
}

int DeleteSubLinkObjLink(unsigned char *p)
{
    char *c = p[8] != 0x15 ? 0 : (char *)p + 0x1C;

    return DeleteTwoWayLink((Link *)(c));
}

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

static int func_00099470(unsigned char *p)
{
    SubLink *c = getSubLink(p);

    if (c->callback) {
        c->callback(p, c->arg);
        c->callback = 0;
    }
    return DeleteTwoWayLink((Link *)getSubLink(p));
}
