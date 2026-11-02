typedef struct FogColMan {
    char pad0[0x90];
    int flags;
    char pad94[4];
    char active[8];
    char free[8];
} FogColMan;

extern FogColMan B_00148A40;

extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

int DeleteCollMan(void *coll)
{
    FogColMan *man = &B_00148A40;
    void **node;
    unsigned char *obj = 0;
    unsigned char *work;

    for (node = isysGroupForFirst(man->free, 0); node != 0; node = isysGroupForNext(node, 0)) {
        obj = *node;
        work = GetObjWork(obj, 0x18);
        if (work == 0 || work != coll) {
            continue;
        }
        *(int *)(work + 0x40) = 0;
        {
            FogColMan *m = &B_00148A40;
            isysAddGroupWithLinkParam(obj, m->active, 0, 0);
            _isysDeleteGroup(obj, m->free, 0);
        }
        break;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    man->flags |= 2;
    return 0;
}
