extern void *DldSysUndefSymbol;
extern int rootPtn;
extern void *memset(void *, int, unsigned int);
extern void *iosMallocAlign(void *, int, int);
extern void *initLayoutObjVU0Secure(char *, void *, int, void *);
extern void *create_and_init_camera_region(int, int, long, void *, void *, void *);
extern int D_00139F44;
extern void **D_00139F48;

typedef struct {
    long id;
    unsigned int ref;
    int pad;
} ColAttrEntry;

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

void init_col_attr_table_segment(int *seg)
{
    ColAttrEntry *e;
    int i;
    int n;
    char buf[0x3C];

    if (D_00139F48 != 0) {
        __asm__ __volatile__("break 0");
        return;
    }
    n = seg[3];
    e = (ColAttrEntry *)seg[4];
    D_00139F44 = n;
    D_00139F48 = iosMallocAlign(&rootPtn, n * 4, 16);
    for (i = 0; i < D_00139F44; i++) {
        void *obj;
        memset(buf, 0, 0x3C);
        obj = initLayoutObjVU0Secure("col_attr_camera_region", &rootPtn, 0, buf);
        D_00139F48[i] = create_and_init_camera_region(1, 0, e[i].id, obj, resourceData(&e[i].ref), &rootPtn);
    }
}
