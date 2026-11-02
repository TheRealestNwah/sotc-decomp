typedef struct LightColMan {
    char pad0[0x514];
    char globalFree[8];
    char globalUsed[8];
    char gameFree[4];
    char gameUsed[4];
    int flags;
} LightColMan;

extern LightColMan *GetLightColMan(void);
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

void DeleteGameLight(void *light)
{
    LightColMan *man = GetLightColMan();
    void **node;
    unsigned char *obj = 0;
    unsigned char *work;

    for (node = isysGroupForFirst(man->gameUsed, 0); node != 0; node = isysGroupForNext(node, 0)) {
        obj = *node;
        work = GetObjWork(obj, 0x1A);
        if (work == 0 || work != light) {
            continue;
        }
        {
            LightColMan *m = GetLightColMan();
            *(int *)(work + 0x2C) = 0;
            isysAddGroupWithLinkParam(obj, m->gameFree, 0, 0);
            _isysDeleteGroup(obj, m->gameUsed, 0);
        }
        break;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    man->flags |= 2;
}
