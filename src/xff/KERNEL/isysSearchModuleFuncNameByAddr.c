typedef struct { unsigned int name; unsigned int value; unsigned int size; unsigned char info; unsigned char other; unsigned short shndx; } ElfSym;
typedef struct { char pad[0x24]; int count; ElfSym *syms; char *strtab; } ModInfo;
typedef struct { char pad[0x1C]; ModInfo *mod; char pad20[0x18]; char *name; } ModObj;
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern char executableModuleGroup[];
extern char *strcpy(char *, const char *);

static inline char *findName(ModInfo *mod, unsigned int address)
{
    int n = mod->count - 1;
    ElfSym *sym = mod->syms;
    char *strtab = mod->strtab;
    while (n--) {
        if (sym->shndx != 0xFFF1 && (sym->info & 0xF) == 2 && sym->value == address)
            return strtab + sym->name;
        sym++;
    }
    return 0;
}

int isysSearchModuleFuncNameByAddr(char *module_name, char *function_name, unsigned int address)
{
    ModObj *object = 0;
    void **link;
    int found = 0;
    for (link = isysGroupForFirst(executableModuleGroup, 0); link != 0;
         link = isysGroupForNext(link, 0)) {
        char *name;
        object = *link;
        name = findName(object->mod, address);
        if (name) {
            if (module_name)
                strcpy(module_name, object->name);
            if (function_name)
                strcpy(function_name, name);
            found = 1;
            break;
        }
    }
    if (object)
        isysGroupForExit(object, 0);
    return found;
}
