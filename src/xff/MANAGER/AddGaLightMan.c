#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
extern char *GetLightColMan();
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);
extern int func_0007B300(unsigned char *, int, int);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

unsigned char *AddGaLightMan(int def, int arg)
{
    char *man;
    void **node;
    unsigned char *last = 0;
    unsigned char *w = 0;
    int found;
    int type = 0x1A;

    man = GetLightColMan();
    found = 0;
    node = isysGroupForFirst(man + 0x524, 0);
    goto test;
    for (;;) {
        node = isysGroupForNext(node, 0);
    test:
        if (node == 0) break;
        {
        char *lman;
        int match;

        last = *node;
        w = GetObjWork(last, type);
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
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    *(int *)(man + 0x52C) |= 4;
    return found ? w : 0;
}
#endif
