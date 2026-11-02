struct DecodedSection {
    void *data;
    char unk4[0x14];
    int allocated;
    char unk1C[0x4];
};

struct DecodedElf {
    char unk0[0x8];
    int next;
    char unkC[0x24];
    struct DecodedSection *sections;
    char unk34[0xC];
    int sectionCount;
};

extern int printf(const char *format, ...);
extern char D_00136100[];

int FreeDecodedSection(struct DecodedElf *elf, void (*freeFunc)(void *)) {
    struct DecodedSection *section;
    int i;

    while (elf != 0) {
        for (i = 1; i < elf->sectionCount; i++) {
            section = &elf->sections[i];
            if (section->allocated != 0) {
                section->allocated = 0;
                freeFunc(section->data);
            }
        }
        if (elf->next == 0) {
            elf = 0;
        } else {
            printf(D_00136100, (char *)elf + elf->next);
            elf = (struct DecodedElf *)((char *)elf + elf->next);
        }
    }
    return 1;
}
