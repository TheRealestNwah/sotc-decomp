struct ElfSection {
    char unk0[4];
    char *data;
    char unk8[0x14];
    int dataOffset;
};

struct ElfSegment {
    char unk0[0xC];
    char *start;
    char *end;
    int startOffset;
    int endOffset;
};

struct ElfInfo {
    char unk0[0x14];
    int unk14;
    char *unk18;
    char unk1C[4];
    char *unk20;
    char unk24[4];
    char *unk28;
    char *unk2C;
    struct ElfSection *sections;
    char *unk34;
    int segmentCount;
    struct ElfSegment *segments;
    int sectionCount;
    char *unk44;
    char *unk48;
    char unk4C[4];
    int unk50;
    int unk54;
    int unk58;
    int sectionsOffset;
    int unk60;
    int segmentsOffset;
    int unk68;
    int unk6C;
};

void RelocateElfInfoHeader(struct ElfInfo *info) {
    int i;

    info->sections = (struct ElfSection *)((char *)info + info->sectionsOffset);
    for (i = 0; i < info->sectionCount; i++) {
        info->sections[i].data = (char *)info + info->sections[i].dataOffset;
    }
    info->unk28 = (char *)info + info->unk54;
    info->unk34 = (char *)info + info->unk60;
    info->unk2C = (char *)info + info->unk58;
    info->unk20 = (char *)info + info->unk50;
    info->segments = (struct ElfSegment *)((char *)info + info->segmentsOffset);
    info->unk48 = (char *)info + info->unk6C;
    info->unk44 = (char *)info + info->unk68;
    for (i = 0; i < info->segmentCount; i++) {
        info->segments[i].start = (char *)info + info->segments[i].startOffset;
        info->segments[i].end = (char *)info + info->segments[i].endOffset;
    }
    info->unk18 = (char *)info + info->unk14;
}
