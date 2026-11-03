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
    char unk8[0x14];
};

struct ElfInfo {
    char unk0[8];
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

extern int printf(const char *format, ...);
extern void RelocateElfInfoHeader(struct ElfInfo *info);
extern void DecodeSection(struct ElfInfo *info, void *a1, void *a2, void *a3);
extern void *memmove(void *dst, const void *src, unsigned int n);
extern void FlushCache(int mode);
extern int LoaderSysPrintf(const char *format, ...);
extern int func_00101AC0();
extern int func_00101AF0();
extern char D_00101AA0[];
extern char D_001364B0[];
extern char D_001364C0[];
extern int ResolveRelocation(struct ElfInfo *info, struct RelocSection *section, int index);
extern char D_00136100[];

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

struct ElfInfo *MoveElf(struct ElfInfo *info, void *dst) {
    void *a1;
    void *a2 = func_00101AF0;
    void *a3 = LoaderSysPrintf;
    int undef;

    LoaderSysPrintf(D_001364B0, info, info->size, dst);
    info = memmove(dst, info, info->size);
    a1 = func_00101AC0;
    FlushCache(0);
    undef = (int)D_00101AA0;
    RelocateElfInfoHeader(info);
    DecodeSection(info, a1, a2, a3);
    RelocateSymbols(info, undef);
    RelocateCodeInline(info);
    FlushCache(0);
    LoaderSysPrintf(D_001364C0, info->entry);
    return info;
}
