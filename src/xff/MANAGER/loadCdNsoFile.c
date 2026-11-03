typedef struct Ptn Ptn;
typedef struct {
    void *model;
    char pad[0x18];
    void *mem;
    void *work;
} ModObj;
extern Ptn rootPtn;
extern int D_00136C10;
extern int B_001498C0[];
extern void *iosMallocInGarbagePtn(int, int);
extern void *iosMallocAlign(Ptn *, int, int);
extern void vschedSetNextFrameForceGarbage(void);
extern void sheetWait(void);
extern void sheetFileRead(void *, void *, int);
extern ModObj *isysCreateModuleObjExisted(void *, int, Ptn *, int, int, int, Ptn *);
extern void isysAddGroupWithLinkParam(ModObj *, int, int, int);
extern void *sheetFileGetDataAdrs(void *);
extern void iosMallocSetExecGarbageCallback(void *, void *, void *);
extern void *isysGetXffEntryPointPreRelocation(void *);
extern void isysResolveOneModuleObj(ModObj *);
extern int shadowGetWorkSize(void *);
extern void shadowModelInit(void *, void *, float);
extern int garbageNsoCallBack();

static inline ModObj *createObj(void *buffer, int work, Ptn *ptn, int garbage)
{
    ModObj *obj = isysCreateModuleObjExisted(buffer, work, ptn, 1, 0, 1, garbage ? 0 : ptn);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, D_00136C10, 0, 0);
    }
    return obj;
}

ModObj *loadCdNsoFile(void *file, int unused, int size)
{
    int work = 0;
    void *getWork;
    Ptn *ptn = &rootPtn;
    int garbage = garbageNsoCallBack != 0;
    void *buffer;
    ModObj *obj;
    getWork = shadowGetWorkSize;

    if (garbage) {
        while ((buffer = iosMallocInGarbagePtn(size, 16)) == 0) {
            vschedSetNextFrameForceGarbage();
            sheetWait();
        }
    } else {
        buffer = iosMallocAlign(ptn, size, 16);
    }
    sheetFileRead(file, buffer, size);
    if (getWork != 0) {
        work = shadowGetWorkSize(isysGetXffEntryPointPreRelocation(buffer));
    }
    obj = createObj(buffer, work, ptn, garbage);
    if (obj != 0) {
        void *objWork = obj->work;
        char *data = sheetFileGetDataAdrs(file);
        B_001498C0[6] += size;
        isysResolveOneModuleObj(obj);
        shadowModelInit(obj->model, objWork, *(float *)(data + 0xC));
        iosMallocSetExecGarbageCallback(obj->mem, garbageNsoCallBack, obj);
    }
    return obj;
}
