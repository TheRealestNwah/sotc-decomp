#ifdef NONMATCHING /* 72 diffs: the inner loop copies its exit test instead of jumping to it, and the 0x1A type load is scheduled after the test */
extern char *GetLightColMan();
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);
extern int func_0007B300(void *, void *, void *);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

void *AddGaLightMan(void *def, void *arg)
{
    char *man;
    unsigned char *w = 0;
    int found;
    void **node;
    unsigned char *last;
    char *lman;
    int match;

    man = GetLightColMan();
    found = 0;
    last = 0;
    for (node = isysGroupForFirst(man + 0x524, 0); node != 0; node = isysGroupForNext(node, 0)) {
        last = *node;
        w = GetObjWork(last, 0x1A);
        if (w == 0) {
            continue;
        }
        match = 0;
        lman = GetLightColMan();
        if (func_0007B300(w, def, arg) != 0) {
            match = 1;
            isysAddGroupWithLinkParam(last, lman + 0x528, 0, 0);
            _isysDeleteGroup(last, lman + 0x524, 0);
        }
        if (match) {
            found = 1;
            break;
        }
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    *(int *)(man + 0x52C) |= 4;
    return found ? w : 0;
}
#endif
