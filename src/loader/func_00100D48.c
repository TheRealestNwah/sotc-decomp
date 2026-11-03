struct sce_stat {
    unsigned int st_mode;
    unsigned int st_attr;
    unsigned int st_size;
    unsigned char st_ctime[8];
    unsigned char st_atime[8];
    unsigned char st_mtime[8];
    unsigned int st_hisize;
    unsigned int st_private[6];
};

struct ElfSym {
    int name;
    int value;
    int size;
    unsigned char info;
    unsigned char other;
    unsigned short shndx;
};

struct ElfSection {
    int addr;
    char unk4[0x1C];
};

struct RelocSection {
    int type;
    int count;
    int unk8;
    int data;
    char unk10[0xC];
};

struct ElfInfo {
    int magic;
    char unk4[4];
    int next;
    char unkC[4];
    int entry;
    int size;
    char unk18[0xC];
    int numSymbols;
    struct ElfSym *symbols;
    char unk2C[4];
    struct ElfSection *sections;
    int *symbolBases;
    int numSections;
    struct RelocSection *relocSections;
};

struct RelocTable {
    struct ElfInfo *info;
    int numSections;
    struct RelocSection *sections;
    void *limit;
};

extern void LoaderSysPrintf(const char *format, ...);
extern int LoaderSysGetstat(const char *name, struct sce_stat *buf);
extern int LoaderSysFOpen(const char *name, int flags, int mode);
extern int LoaderSysFRead(int fd, void *buf, int size);
extern int LoaderSysFClose(int fd);
extern void PutString(int attr, const char *format, ...);
extern int printf(const char *format, ...);
extern int sprintf(char *buf, const char *format, ...);
extern void RelocateElfInfoHeader(struct ElfInfo *info);
extern void DecodeSection(struct ElfInfo *info, void *a1, void *a2, void *a3);
extern int ResolveRelocation(struct ElfInfo *info, struct RelocSection *section, int index);
extern void func_00101B88(struct ElfInfo *info, int a1, struct RelocTable *table);
extern int OutputLinkerScriptFile(struct ElfInfo *info, const char *path, void *cb);
extern int func_00101AC0();
extern int func_00101AF0();
extern char D_00101AA0[];
extern unsigned int D_00139E04;
extern int D_00131CB8[];
extern char D_00136100[];
extern char D_00136448[];
extern char D_00136460[];
extern char D_00136488[];
extern char D_00139E58[];

static inline unsigned int AllocHeap(unsigned int size, unsigned int align) {
    unsigned int addr = (D_00139E04 + align - 1) / align * align;

    D_00139E04 = addr + size;
    return addr;
}

static inline void RelocateSymbols(struct ElfInfo *info, int undefValue) {
    struct ElfSym *sym;
    struct ElfSection *sections;
    int *base;
    int i;

    i = info->numSymbols;
    sym = info->symbols;
    base = info->symbolBases;
    sections = info->sections;
    for (i--; i != -1; i--, sym++, base++) {
        unsigned int shndx = sym->shndx;

        switch (shndx) {
            case 0:
                sym->value = undefValue;
                break;
            case 0xFFF1:
                sym->value = *base;
                break;
            default:
                if (shndx >= 0xFF00) {
                    break;
                }
                switch (sym->info & 0xF) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        sym->value = *base + sections[shndx].addr;
                        break;
                }
                break;
        }
    }
}

static inline int RelocateCodeInline(struct ElfInfo *info) {
    struct RelocSection *section;
    int i;
    int j;
    int count;

    while (info != 0) {
        i = info->numSections;
        section = info->relocSections;
        for (i--; i != -1; i--, section++) {
            if (section->type == 4 || section->type == 9) {
                count = section->count;
                for (j = 0; j < count; j++) {
                    ResolveRelocation(info, section, j);
                }
            }
        }
        if (info->next == 0) {
            info = 0;
        } else {
            printf(D_00136100, (char *)info + info->next);
            info = (struct ElfInfo *)((char *)info + info->next);
        }
    }
    return 1;
}

static inline void RelocateTable(struct ElfInfo *info, struct RelocTable *table) {
    struct RelocSection *section;
    int i;
    int j;
    int count;

    i = table->numSections;
    section = table->sections;
    for (i--; i != -1; i--, section++) {
        if (section->type == 4 || section->type == 9) {
            count = section->count;
            for (j = 0; j < count; j++) {
                ResolveRelocation(info, section, j);
            }
        }
    }
}

struct ElfInfo *func_00100D48(const char *name) {
    struct sce_stat st;
    struct RelocTable table;
    char path[0x400];
    unsigned long size;
    struct ElfInfo *info;
    unsigned char *p;
    int fd;
    int n;
    int sum;
    int total;
    int i;

    LoaderSysPrintf(D_00136448, name);
    fd = LoaderSysGetstat(name, &st);
    if (fd != 0) {
        PutString(-0x100, D_00136460, name, fd);
        return 0;
    }
    fd = LoaderSysFOpen(name, 1, 0);
    if (fd < 0) {
        PutString(-0x100, D_00136460, name, fd);
        return 0;
    }
    size = ((unsigned long)st.st_hisize << 32) | st.st_size;
    info = (struct ElfInfo *)AllocHeap((int)size, 0x40);
    LoaderSysFRead(fd, info, (int)size);
    LoaderSysFClose(fd);

    sum = 0;
    p = (unsigned char *)info;
    i = (int)size;
    while (i--) {
        sum += *p++;
    }
    LoaderSysPrintf(D_00136488, info, (char *)info + (int)size, size, sum);

    table.info = info;
    table.numSections = 0;
    table.sections = (struct RelocSection *)0x1000000;
    table.limit = (void *)0x1100000;
    RelocateElfInfoHeader(info);
    if (info->magic == D_00131CB8[0]) {
        n = info->numSections >> 1;
        total = 0;
        for (i = 0; i < n; i++) {
            total += info->relocSections[i].count;
        }
        func_00101B88(info, info->relocSections->data + total * 8, &table);
        for (i = 0; i < n; i++) {
            info->relocSections[n + i].count = 0;
        }
    }
    DecodeSection(info, func_00101AC0, func_00101AF0, LoaderSysPrintf);
    RelocateSymbols(info, (int)D_00101AA0);
    RelocateCodeInline(info);
    RelocateTable(info, &table);
    sprintf(path, D_00139E58, name);
    OutputLinkerScriptFile(info, path, LoaderSysPrintf);
    return info;
}
