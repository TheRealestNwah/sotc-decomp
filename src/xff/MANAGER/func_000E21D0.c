extern char rootPtn[];
extern char *_isysCreateObj(void *, int, int, int, int, int);
extern int isysGetXffWorkSize(int);
extern void isysInitModuleObjExisted(char *, int, int, int, int, void *);
extern int isysDisposeModuleObjRelocationElement(char *);
extern int isysSearchSymbol(int *, int);
extern int isysGetModuleObjMallocSize(char *);
extern void AddObjectManagerSheetWorkSize(int);
extern char *D_00139F14;

#ifdef NONMATCHING
/* 2 diffs: the store to o+0x38 and the h+4 addiu come out swapped (isysSearchSymbol and isysDisposeModuleObjRelocationElement return int) */
static char *func_000E21D0(int id, int xff)
{
    char *o = _isysCreateObj(rootPtn, 4, 0x4C, isysGetXffWorkSize(xff), 0, 8);
    char *h;
    int i;

    *(int *)(o + 0x3C) = id;
    *(int *)(o + 0x40) = 0;
    isysInitModuleObjExisted(o, xff, 1, 1, 1, rootPtn);
    isysDisposeModuleObjRelocationElement(o);
    if (*(int *)(o + 0x48) == 0) {
        *(int *)(o + 0x48) = -1;
        if ((*(char **)(o + 0x44) = D_00139F14) != 0)
            *(char **)(D_00139F14 + 0x48) = o;
        D_00139F14 = o;
    }
    h = *(char **)(o + 0x20);
    *(char **)(o + 0x38) = h;
    isysSearchSymbol((int *)(h + 4), *(int *)(h + 4));
    isysSearchSymbol((int *)(h + 8), *(int *)(h + 8));
    for (i = 0; i < *(int *)(h + 0x18); i++) {
        char *e = *(char **)(h + 0x1C) + i * 0xC;
        isysSearchSymbol((int *)(e + 4), *(int *)(e + 4));
        isysSearchSymbol((int *)(e + 8), *(int *)(e + 8));
    }
    *(char **)(*(char **)(o + 0x38) + 0x2C) = o;
    AddObjectManagerSheetWorkSize((**(int **)(*(char **)o - 4) & 0xFFFFFF) * 4);
    AddObjectManagerSheetWorkSize(isysGetModuleObjMallocSize(o));
    return o;
}
#endif
