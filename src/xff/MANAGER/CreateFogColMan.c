typedef struct FogColMan {
    char pad0[0x98];
    char free[8];
} FogColMan;

extern FogColMan B_00148A40;

extern unsigned char *_isysCreateObj(void *, int, int, int, int, int);
extern void *memset(void *, int, unsigned int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
static void func_00072348(unsigned char *);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

void CreateFogColMan(void *heap)
{
    FogColMan *man = &B_00148A40;
    unsigned char *obj;
    unsigned char *work;
    int i;

    for (i = 0; i < 0x80; i++) {
        obj = _isysCreateObj(heap, 0x18, 0xB0, 0xB0, (int)func_00072348, 0x10);
        if (obj == 0) {
            continue;
        }
        work = GetObjWork(obj, 0x18);
        if (work != 0) {
            memset(work, 0, 0x90);
        }
        *(short *)(work + 0x4C) = i;
        isysAddGroupWithLinkParam(obj, man->free, 0, 0);
    }
}
