typedef struct {
    int heap;
    char pad4[8];
    unsigned char first;
    char padD[3];
    int unk10;
    char pad14[8];
    int unk1C;
    char pad20[4];
    int unk24;
} ModInfo;
typedef struct {
    unsigned int rest : 29;
    unsigned int c : 1;
    unsigned int b : 1;
    int a : 1;
} ModFlags;

typedef struct {
    int heap;
    char pad4[0x18];
    ModInfo *info;
    int unk20;
    char pad24[8];
    ModFlags flags;
    char list[8];
    char *name;
    int unk3C;
} ModObj;

extern char *D_00040904;
extern char rootPtn[];
extern char needResolveModuleGroup[], symbolDefModuleGroup[], executableModuleGroup[];
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void func_00007968(ModObj *, int);
extern void func_00007F80(void *, void *, ModInfo *);
extern void *iosMallocAlign(int, int, int);
extern int strlen(const char *);
extern char *strcpy(char *, const char *);

static ModObj *func_00008CE0(char *name, ModInfo *info, void *heap)
{
    ModObj *obj;
    int n, d, x, t;

    n = info->first ? info->first + 1 : 2;
    d = info->unk24 - info->unk1C - n;
    x = d ? d * 16 + 0x33 : 0;
    t = info->unk1C ? x + info->unk1C * 16 + 0x33 : x;
    obj = _isysCreateObj(heap, 2, 0x40, strlen(name) + t + 1, 0, 4);
    obj->unk20 = info->unk10;
    obj->flags.a = 0;
    obj->info = info;
    obj->flags.b = 0;
    obj->flags.c = 0;
    if (info->unk24 != 0) {
        isysAddGroupWithLinkParam(obj, symbolDefModuleGroup, 0, 0);
    }
    if (info->unk1C != 0) {
        isysAddGroupWithLinkParam(obj, needResolveModuleGroup, 0, 0);
    }
    func_00007968(obj, obj->heap);
    func_00007F80(obj->list, rootPtn, info);
    if (name != 0) {
        obj->name = iosMallocAlign(obj->heap, strlen(name) + 1, 1);
        strcpy(obj->name, name);
    } else {
        obj->name = D_00040904;
    }
    isysAddGroupWithLinkParam(obj, executableModuleGroup, 0, 0);
    obj->unk3C = 0;
    return obj;
}
