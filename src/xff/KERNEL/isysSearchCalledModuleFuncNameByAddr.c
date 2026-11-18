extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern char executableModuleGroup[];
#ifdef NONMATCHING
/* 1 word differs: operand order of addu a3 at 0xC8 */
extern char *strcpy(char *, const char *);
typedef struct Sect { unsigned int addr; int pad4; unsigned int size; char padC[0x14]; } Sect;
typedef struct Sym { int name; char pad4[0xA]; unsigned short shndx; } Sym;
typedef struct Rel { unsigned int offset; unsigned int info; } Rel;
typedef struct RelSect { int type; unsigned int count; int sect; Rel *rel; char pad10[0xC]; } RelSect;
typedef struct ElfInfo {
    char pad0[0x28];
    Sym *sym;
    char *str;
    Sect *sect;
    char pad34[4];
    int nrel;
    RelSect *rels;
    int nsect;
} ElfInfo;
typedef struct Module { char pad0[0x1C]; ElfInfo *elf; char pad20[0x18]; char *name; } Module;


static int func_0000AC30(char *module_name, char *function_name, Module *m, unsigned int address)
{
    ElfInfo *e = m->elf;
    int i, j;
    unsigned int k;
    Sect *s;
    RelSect *r;
    Rel *rel;
    Sym *sym;
    char *name;

    if (e == 0)
        return 0;
    for (i = 0; i < e->nsect; i++) {
        s = &e->sect[i];
        if (s->addr == 0 || address < s->addr || address >= s->addr + s->size)
            continue;
        if (module_name != 0)
            strcpy(module_name, m->name);
        if (function_name == 0)
            return 1;
        for (j = 0; j < e->nrel; j++) {
            if (e->rels[j].type != 4 && e->rels[j].type != 9)
                continue;
            for (k = 0; k < e->rels[j].count; k++) {
                rel = &e->rels[j].rel[k];
                sym = &e->sym[rel->info >> 8];
                if (sym->shndx == 0 && e->sect[e->rels[j].sect].addr + rel->offset == address) {
                    name = e->str + sym->name;
                    goto found;
                }
            }
        }
        name = 0;
    found:
        if (name != 0) {
            strcpy(function_name, name);
            return 1;
        }
        strcpy(function_name, "*can't search(static or tail call?)*");
        return 2;
    }
    return 0;
}
#else
extern int func_0000AC30(char *, char *, void *, unsigned int);
#endif
int isysSearchCalledModuleFuncNameByAddr(char *module_name, char *function_name, unsigned int address)
{
    void *object = 0;
    void **link;
    int found = 0;
    int result;
    for (link = isysGroupForFirst(executableModuleGroup, 0); link != 0;
         link = isysGroupForNext(link, 0)) {
        object = *link;
        result = func_0000AC30(module_name, function_name, object, address);
        if (result) {
            found = result;
            break;
        }
    }
    if (object)
        isysGroupForExit(object, 0);
    return found;
}
