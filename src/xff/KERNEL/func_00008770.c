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

extern char D_0000A208[];
extern int func_0000A250();
extern char D_0000A208[];
extern int func_0000A298();
extern int func_0000A350();
extern int func_000077C0();
extern int DldSysUndefSymbol;
extern char rootPtn[];
extern char needResolveModuleGroup[], symbolDefModuleGroup[];
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern ModInfo *func_00007B78(ModInfo *, ModObj *, int, void *, void *, int, void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void func_00007968(ModObj *, int);
extern void func_00007F80(void *, void *, ModInfo *);

extern void *iosMallocAlign(void *, int, int);
extern int func_0000A1A8(void *, void *, int);

/* Parked: 3 diffs: n=2 branch order inverted */
#ifdef NONMATCHING
ModObj *func_00008770(void *name, int size, void *heap, int sym, int res, int link)
{
    int saved;
    ModObj *obj;
    ModInfo *mod;
    ModInfo *r;
    ModInfo *info;
    int found;
    int n, d, x;

    mod = iosMallocAlign(rootPtn, size, 0x10);
    func_0000A1A8(mod, name, size);
    n = 2;
    if (mod->first != 0) {
        n = mod->first + 1;
    }
    d = mod->unk24 - mod->unk1C - n;
    x = d ? d * 16 + 0x33 : 0;
    if (mod->unk1C != 0) {
        x = x + mod->unk1C * 16 + 0x33;
    }
    saved = 0;
    obj = _isysCreateObj(heap, 1, 0x38, x, (int)func_0000A350, 4);
    obj->flags.a = 0;
    r = func_00007B78(mod, obj, obj->heap, D_0000A208, func_0000A298, DldSysUndefSymbol, func_000077C0, 0);
    if (r != 0) {
        saved = obj->flags.a;
    }
    info = r ? r : mod;
    obj->unk20 = r ? r->heap : mod->unk10;
    obj->info = info;
    obj->flags.a = 0;
    obj->flags.b = found = (r != 0);
    obj->flags.c = 0;
    if (!found) {
        if (info->unk24 != 0 && sym != 0) {
            isysAddGroupWithLinkParam(obj, symbolDefModuleGroup, 0, 0);
        }
        if (info->unk1C != 0 && res != 0) {
            isysAddGroupWithLinkParam(obj, needResolveModuleGroup, 0, 0);
        }
        if (link != 0) {
            func_00007968(obj, obj->heap);
        }
        func_00007F80(obj->list, rootPtn, info);
    }
    if (r != 0) {
        obj->flags.a = saved;
    }
    return obj;
}
#else
extern ModObj *func_00008770(void *name, int size, void *heap, int sym, int res, int link);
#endif
