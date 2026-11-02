struct ElfSym {
    unsigned int name;
    unsigned int value;
    unsigned int size;
    unsigned char info;
    unsigned char other;
    unsigned short shndx;
};

struct ElfSection {
    unsigned int addr;
    char unk4[0x1C];
};

struct ElfInfo {
    char unk0[0x24];
    int symCount;
    struct ElfSym *syms;
    int unk2C;
    struct ElfSection *sections;
    unsigned int *symBase;
};

int RelocateSelfSymbol(struct ElfInfo *info, unsigned int base) {
    int count = info->symCount;
    struct ElfSym *sym = info->syms;
    unsigned int *symBase = info->symBase;
    struct ElfSection *sections = info->sections;
    unsigned int shndx;

    while (count-- != 0) {
        shndx = sym->shndx;
        switch (shndx) {
        case 0:
            sym->value = base;
            break;
        case 0xFFF1:
            sym->value = *symBase;
            break;
        default:
            if (shndx < 0xFF00) {
                switch (sym->info & 0xF) {
                case 0:
                case 1:
                case 2:
                case 3:
                    sym->value = *symBase + sections[shndx].addr;
                    break;
                }
            }
            break;
        }
        sym++;
        symBase++;
    }
    return 1;
}
