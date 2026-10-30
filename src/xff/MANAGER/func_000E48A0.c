extern const char RO_0013B1F0[];
extern void **D_00139F10;
extern char rootPtn[];
extern void iosJumpRecoverPoint(const char *, ...);
extern int isysGetXffWorkSize(void *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysInitGroup(void *);
extern void func_000E2808(void *, void *, void *);

typedef struct {
    char pad0[0x3C];
    void *parent;
    int xff;
    unsigned int low : 19;
    unsigned int flag : 1;
    unsigned int state : 10;
    unsigned int high : 2;
    char group[0x10];
    int count;
    int list;
} PartObj;

static PartObj *func_000E48A0(void *xff, void *arg, int index)
{
    void *parent = D_00139F10[index];
    PartObj *obj;

    if (parent == 0)
        iosJumpRecoverPoint(RO_0013B1F0 + 0x6AE8, index);
    obj = _isysCreateObj(rootPtn, 5, 0x60, isysGetXffWorkSize(xff), 0, 8);
    obj->parent = parent;
    obj->count = 0;
    obj->list = 0;
    obj->state = 0;
    obj->flag = 0;
    isysInitGroup(obj->group);
    if (xff)
        func_000E2808(xff, arg, obj);
    else
        obj->xff = 0;
    return obj;
}
