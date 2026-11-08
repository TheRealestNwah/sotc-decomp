typedef struct {
    int heap;
    char pad4[0xC];
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
extern int func_000077C0();
extern int DldSysUndefSymbol;
extern char *D_00040904;
extern char rootPtn[];
extern char executableModuleGroup[], needResolveModuleGroup[], symbolDefModuleGroup[];
extern ModInfo *func_00007B78(ModInfo *, ModObj *, int, void *, void *, int, void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void func_00007968(ModObj *, int);
extern void func_00007F80(void *, void *, ModInfo *);
extern int strlen(const char *);
extern char *strcpy(char *, const char *);
extern void *iosMallocAlign(int, int, int);

static int func_000089C0(ModObj *obj, char *name, ModInfo *mod)
{
    int saved = 0;
    ModInfo *r;
    ModInfo *info;
    int found;

    obj->flags.a = 0;
    r = func_00007B78(mod, obj, obj->heap, D_0000A208, func_0000A250, DldSysUndefSymbol, func_000077C0, 0);
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
        if (info->unk24 != 0) {
            isysAddGroupWithLinkParam(obj, symbolDefModuleGroup, 0, 0);
        }
        if (info->unk1C != 0) {
            isysAddGroupWithLinkParam(obj, needResolveModuleGroup, 0, 0);
        }
        func_00007968(obj, obj->heap);
        func_00007F80(obj->list, rootPtn, info);
    }
    if (r != 0) {
        obj->flags.a = saved;
    }
    if (name != 0) {
        obj->name = iosMallocAlign(obj->heap, strlen(name) + 1, 1);
        strcpy(obj->name, name);
    } else {
        obj->name = D_00040904;
    }
    isysAddGroupWithLinkParam(obj, executableModuleGroup, 0, 0);
    obj->unk3C = 0;
    return 1;
}
