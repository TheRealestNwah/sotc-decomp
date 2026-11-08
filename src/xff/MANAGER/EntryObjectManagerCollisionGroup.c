extern char *D_00136C10;
extern char *GetLayoutClass(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupRelativeWithLinkParam(void *, void *, void *, int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

void EntryObjectManagerCollisionGroup(void *obj, char *def)
{
    int i;
    char *groups = D_00136C10 + 0x60;
    int *flags = (int *)(def + 0x10);

    *(int *)(*(char **)(GetLayoutClass(obj) + 0x174) + 0x20) = *(short *)(def + 0xC);
    for (i = 0; i < 16; flags++, i++) {
        void **node;
        void *last;
        int found;
        void *grp;
        if (*flags != 0) {
        grp = groups + 4 + i * 4;
        found = 0;
        last = 0;
        for (node = isysGroupForFirst(grp, 0); node != 0; node = isysGroupForNext(node, 0)) {
            last = *node;
            if (*(int *)(*(char **)(GetLayoutClass(last) + 0x174) + 0x20) < *(short *)(def + 0xC)) {
                continue;
            }
            isysAddGroupRelativeWithLinkParam(obj, grp, node, 0, 0, 0);
            found = 1;
            break;
        }
        if (last != 0) {
            isysGroupForExit(last, 0);
        }
        if (!found) {
            isysAddGroupWithLinkParam(obj, grp, 0, 0);
        }
        }
    }
}
