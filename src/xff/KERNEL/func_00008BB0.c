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
    char pad0[0x3C];
    int size;
} ModObj;

extern int D_00040900;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern int func_0000A1A8(void *, void *, int);
extern int func_0000A440();
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern int strlen(const char *);
extern int func_000089C0(ModObj *, char *, ModInfo *);

static ModObj *func_00008BB0(char *name, int size, void *heap)
{
    int old = D_00040900;
    ModInfo *mod;
    ModObj *obj;
    int n, d, x, t;

    mod = iosMallocAlign(rootPtn, size, 0x40);
    func_0000A1A8(mod, name, size);
    n = mod->first ? mod->first + 1 : 2;
    d = mod->unk24 - mod->unk1C - n;
    x = d ? d * 16 + 0x33 : 0;
    t = mod->unk1C ? x + mod->unk1C * 16 + 0x33 : x;
    obj = _isysCreateObj(heap, 2, 0x40, strlen(name) + t + 1, (int)func_0000A440, 4);
    func_000089C0(obj, name, mod);
    D_00040900 += size;
    obj->size = D_00040900 - old;
    return obj;
}
