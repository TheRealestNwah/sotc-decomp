struct RelocSection {
    int type;
    int count;
    int unk8;
    int data;
    int data2;
    int unk14;
    int unk18;
};

struct ElfInfo {
    char unk0[0x38];
    int numSections;
    struct RelocSection *relocSections;
};

/* The copied table uses its own struct type with pointer fields. The source keeps
   int fields, so stores through dst don't alias loads through src, and the
   scheduler can hoist the src->data2 load above the dst->data store as the
   original does. */
struct RelocOut {
    int type;
    int count;
    int unk8;
    char *data;
    char *data2;
    int unk14;
    int unk18;
};

struct RelocTable {
    struct ElfInfo *info;
    int numSections;
    struct RelocOut *sections;
    char *limit;
};

extern void LoaderSysPrintf(const char *format, ...);
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern char D_00136400[];
extern int D_00139E04;

int func_00101B88(struct ElfInfo *info, int a1, struct RelocTable *table) {
    struct RelocSection *src;
    struct RelocOut *dst;
    char *p;
    int n;
    int i;
    int size;

    info = table->info;
    dst = table->sections;
    n = info->numSections >> 1;
    p = table->limit;
    src = &info->relocSections[n];
    for (i = 0; i < n; i++) {
        size = src->count * 8;
        *dst = *(struct RelocOut *)src;
        memcpy(p, (void *)src->data, size);
        dst->data = p;
        p += size;
        memcpy(p, (void *)src->data2, size);
        dst->data2 = p;
        p += size;
        src++;
        dst++;
    }
    LoaderSysPrintf(D_00136400, a1, table->sections, dst, table->limit, p);
    table->numSections = n;
    D_00139E04 = a1;
    return 0;
}
