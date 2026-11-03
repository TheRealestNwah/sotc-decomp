struct RelocSection {
    int type;
    int count;
    char unk8[0x14];
};

struct ElfInfo {
    char unk0[8];
    int next;
    char unkC[0x2C];
    int numSections;
    struct RelocSection *sections;
};

extern int printf(const char *format, ...);
extern int ResolveRelocation(struct ElfInfo *info, struct RelocSection *section, int index);
extern char D_00136100[];

int RelocateCode(struct ElfInfo *info) {
    struct RelocSection *section;
    int i;
    int j;
    int count;

    while (info != 0) {
        i = info->numSections;
        section = info->sections;
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


