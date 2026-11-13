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
    {
        register int sz __asm__("$5") = info->size;
        register RelElem *rl __asm__("$4") = info->rel;
        register int off __asm__("$2") = n * 28;
        register RelElem *e2 __asm__("$2") = (RelElem *)(off + (int)rl);
        register char *dt __asm__("$3") = e2->data;
        register int dd __asm__("$3") = dt - (char *)info;
        return sz - dd;
    }
}
