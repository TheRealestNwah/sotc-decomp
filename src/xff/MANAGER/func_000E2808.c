extern char rootPtn[];
extern void isysInitModuleObjExisted(char *, int, int, int, int, void *);
extern int isysDisposeModuleObjRelocationElement(char *);
extern void isysRelocateModuleObj(char *, int);
extern int isysSearchSymbol(int *, int);
extern int isysGetModuleObjMallocSize(char *);
extern void AddObjectManagerSheetWorkSize(int);
extern void iosJumpRecoverPoint(const char *, ...);
extern char *D_00139F18;
extern char RO_00141C00[];

static void func_000E2808(int xff, int id, char *o)
{
    char *h;
    char *m;
    int *p;
    int i;
    int n;
    int j;
    int k;
    int stride;
    int *dst;

    *(unsigned int *)(o + 0x44) = (*(unsigned int *)(o + 0x44) & 0xFFF80000) | (id & 0x7FFFF);
    isysInitModuleObjExisted(o, xff, 1, 1, 1, rootPtn);
    isysDisposeModuleObjRelocationElement(o);
    if (*(int *)(o + 0x5C) == 0) {
        *(int *)(o + 0x5C) = -1;
        if ((*(char **)(o + 0x58) = D_00139F18) != 0)
            *(char **)(D_00139F18 + 0x5C) = o;
        D_00139F18 = o;
    }
    isysRelocateModuleObj(o, *(int *)(o + 0x40) = *(int *)(o + 0x1C));
    h = *(char **)(o + 0x20);
    *(char **)(o + 0x38) = h;
    p = (int *)(h + 8);
    *(char **)(h + 0x14) = o;
    *(int *)(o + 0x54) = *(int *)(*(char **)(o + 0x3C) + 0x40);
    *(int *)(*(char **)(o + 0x3C) + 0x40) = (int)o;
    if (isysSearchSymbol(p, *p) == 0) {
        iosJumpRecoverPoint(RO_00141C00, **(int **)(*(char **)(o + 0x3C) + 0x38), *(int *)h, *p);
        __asm__ __volatile__("break 0");
    }
    n = *(int *)(h + 0x20);
    m = *(char **)(*(char **)(o + 0x3C) + 0x38);
    p = *(int **)(h + 0x24) + 1;
    i = n - 1;
    while (i-- > 0) {
        if (isysSearchSymbol(p, *p) == 0) {
            iosJumpRecoverPoint(RO_00141C00, *(int *)m, *(int *)h, *p);
            __asm__ __volatile__("break 0");
        }
        p++;
    }
    dst = *(int **)(h + 0x10);
    stride = *(int *)(m + 0xC);
    for (j = 0; j < *(int *)(h + 0xC); j++) {
        for (k = 0; k < *(int *)(m + 0x20); k++) {
            int *q = (int *)((char *)dst + ((int *)*(int *)(m + 0x24))[k]);
            if (*q != 0)
                *q = (*(int **)(h + 0x24))[*q];
        }
        dst = (int *)((char *)dst + stride);
    }
    AddObjectManagerSheetWorkSize((**(int **)(*(char **)o - 4) & 0xFFFFFF) * 4);
    AddObjectManagerSheetWorkSize(isysGetModuleObjMallocSize(o));
}
