struct RelocSection {
    int unk0;
    int size;
    int unk8;
    int addr;
    char unk10[0xC];
};

struct RelocElement {
    int magic;
    char unk4[0x34];
    int count;
    struct RelocSection *sections;
};

extern int D_00131CB8[];

void DisposeRelocationElement(struct RelocElement *elem, void (*dispose)(struct RelocElement *elem, int addr, int arg), int arg) {
    if (elem->magic == D_00131CB8[0]) {
        int n = elem->count >> 1;
        int total = 0;
        int i;

        for (i = 0; i < n; i++) {
            total += elem->sections[i].size;
        }
        dispose(elem, elem->sections[0].addr + total * 8, arg);
        for (i = 0; i < n; i++) {
            elem->sections[n + i].size = 0;
        }
    }
}
