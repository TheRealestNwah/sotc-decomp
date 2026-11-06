typedef struct Ptn Ptn;
typedef struct {
    char pad[0x2C];
    unsigned int flags;
} ModuleObj;
typedef struct {
    char pad[0x28];
    int size;
} BinarySize;

extern Ptn rootPtn;
extern int D_00136C10;
extern BinarySize B_001498C0;
extern void *iosMallocInGarbagePtn(int, int);
extern void vschedSetNextFrameForceGarbage(void);
extern void sheetWait(void);
extern void sheetFileRead(void *, void *, int);
extern ModuleObj *isysCreateModuleObjExisted(void *, int, Ptn *, int, int, int, Ptn *);
extern int isysAddGroupWithLinkParam(ModuleObj *, int, int, int);
extern void iosJumpRecoverPoint(void *, ...);

static inline ModuleObj *createModule(void *buf, Ptn *ptn, int flag)
{
    ModuleObj *obj = isysCreateModuleObjExisted(buf, 0, ptn, 1, 0, 1, flag == 0 ? ptn : 0);

    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, D_00136C10, 0, 0);
        if (!(obj->flags & 0x40000000)) {
            iosJumpRecoverPoint("objman:\t\272\306\307\333\303\326\311\324\307\275\262\275\274\272\307\324\n");
        }
    }
    return obj;
}

ModuleObj *loadCdXffFile(void *f, int unused, int size)
{
    void *b;
    ModuleObj *obj;
    Ptn *ptn = &rootPtn;
    int flag = 0;

    while ((b = iosMallocInGarbagePtn(size, 16)) == 0) {
        vschedSetNextFrameForceGarbage();
        sheetWait();
    }
    sheetFileRead(f, b, size);
    obj = createModule(b, ptn, flag);
    if (obj != 0) {
        B_001498C0.size += size;
    }
    return obj;
}
