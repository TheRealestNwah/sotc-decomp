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

/* Parked: 6 diffs (needs -fno-strict-aliasing): the return expression puts rel, size and data in different temporaries */
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
        info->rel[n + i].count = 0;
    }
    e = info->rel + n;
    return info->size - (e->data - (char *)info);
}
#else
extern int isysDisposeModuleObjRelocationElement(RelObj *obj);
#endif
