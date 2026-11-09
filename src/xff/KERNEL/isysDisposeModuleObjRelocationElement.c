typedef struct {
    int unk0;
    int count;
    int unk8;
    char *data;
    char pad10[0xC];
} RelElem;

typedef struct {
    int magic;
    char pad4[0x10];
    int size;
    char pad18[0x20];
    int nrel;
    RelElem *rel;
} RelInfo;

typedef struct {
    char pad0[0x1C];
    RelInfo *info;
} RelObj;

extern int D_00040908;
extern void func_0000A748(RelInfo *, char *, int);

/* Parked: 35 diffs: info/n swap between s0 and s1, and the clear loop reloads info->rel each pass in the original */
#ifdef NONMATCHING
int isysDisposeModuleObjRelocationElement(RelObj *obj)
{
    RelInfo *info = obj->info;
    int n;
    int total;
    int i;
    RelElem *e;

    if (info->magic != D_00040908) {
        return 0;
    }
    n = info->nrel >> 1;
    total = 0;
    for (i = 0; i < n; i++) {
        total += info->rel[i].count;
    }
    func_0000A748(info, info->rel->data + total * 8, 0);
    for (i = 0; i < n; i++) {
        e = &info->rel[i];
        e->count = 0;
    }
    return info->size - (info->rel[n].data - (char *)info);
}
#else
extern int isysDisposeModuleObjRelocationElement(RelObj *obj);
#endif
