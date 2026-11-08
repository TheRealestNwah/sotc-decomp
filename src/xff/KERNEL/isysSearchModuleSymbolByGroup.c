typedef struct { int key; int a; int *sym; } Ent;
typedef struct { int name; int value; int size; char info; char other; unsigned short shndx; } Sym;
typedef struct { char pad0[0x24]; int nsyms; Sym *syms; char *strtab; } ModInfo;
typedef struct { char pad0[0x1C]; ModInfo *info; char pad20[0xC]; unsigned int flags; } Module;

extern char B_00054398[];
extern int MakeStrHashValue(char *);
extern Ent *SearchStrHashKey(void *, int);
extern int strcmp(const char *, const char *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

static inline int search_symbol(int *out, char *name, Module *mod)
{
    int hash = MakeStrHashValue(name);
    ModInfo *info = mod->info;

    if (mod->flags & 0x80000000) {
        Ent *e = SearchStrHashKey(B_00054398, hash);
        if (e != 0) {
            *out = e->sym[1];
            return 1;
        }
    } else {
        Sym *s = info->syms;
        int n = info->nsyms - 2;
        char *strtab = info->strtab;
        while (n != -1) {
            if (s->shndx != 0 && strcmp(strtab + s->name, name) == 0) {
                *out = s->value;
                return 1;
            }
            n--;
        }
    }
    return 0;
}

Module *isysSearchModuleSymbolByGroup(int *out, char *name, void *group, Module *skip)
{
    Module *mod = 0;
    Module *found = 0;
    void **link;

    for (link = isysGroupForFirst(group, 0); link != 0; link = isysGroupForNext(link, 0)) {
        mod = *link;
        if (mod == skip) {
            continue;
        }
        if (search_symbol(out, name, mod)) {
            found = mod;
            break;
        }
    }
    if (mod != 0) {
        isysGroupForExit(mod, 0);
    }
    return found;
}
