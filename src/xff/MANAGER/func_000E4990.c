typedef struct {
    char unknown00[0x3C];
    void *sheet;
    int unknown40;
    unsigned int unknown44_0 : 19;
    unsigned int ready : 1;
    unsigned int unknown44_20 : 10;
    unsigned int unknown44_30 : 2;
    char group[0x10];
    int unknown58;
    int unknown5C;
} SheetObj;

extern const char RO_0013B1F0[];
extern void **D_00139F10;
extern char rootPtn[];
extern void iosJumpRecoverPoint(const char *, ...);
extern int isysGetXffWorkSize(void *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysInitGroup(void *);
extern void func_000E2808(void *, void *, SheetObj *);

static SheetObj *func_000E4990(void *xff, void *arg, int id)
{
    void *sheet = D_00139F10[id];
    SheetObj *obj;

    if (!sheet)
        iosJumpRecoverPoint(RO_0013B1F0 + 0x6AE8, id);
    obj = _isysCreateObj(rootPtn, 5, 0x60, isysGetXffWorkSize(xff), 0, 8);
    obj->sheet = sheet;
    obj->unknown44_20 = 0;
    obj->unknown58 = 0;
    obj->ready = 0;
    obj->unknown5C = 0;
    isysInitGroup(obj->group);
    if (xff)
        func_000E2808(xff, arg, obj);
    else
        obj->unknown40 = 0;
    obj->ready = 1;
    return obj;
}
