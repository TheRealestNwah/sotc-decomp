typedef struct Ptn Ptn;
typedef struct {
    char pad[0x1C];
    void *mem;
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
extern int texGetWorkSize(void *);
extern void texInitialize(ModObj *, void *);
extern int garbageNtoCallBack();

static inline ModObj *createObj(void *buffer, int work, Ptn *ptn, int garbage)
{
    ModObj *obj = isysCreateModuleObjExisted(buffer, work, ptn, 1, 0, 1, garbage ? 0 : ptn);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, D_00136C10, 0, 0);
    }
    return obj;
}

ModObj *loadCdNtoFile(void *file, int unused, int size)
{
    int work = 0;
    void *getWork;
    void *data = sheetFileGetDataAdrs(file);
    Ptn *ptn = &rootPtn;
    int garbage = garbageNtoCallBack != 0;
    void *buffer;
    ModObj *obj;
    getWork = texGetWorkSize;

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
        work = texGetWorkSize(isysGetXffEntryPointPreRelocation(buffer));
    }
    obj = createObj(buffer, work, ptn, garbage);
    if (obj != 0) {
        B_001498C0[7] += size;
        texInitialize(obj, data);
        iosMallocSetExecGarbageCallback(obj->mem, garbageNtoCallBack, obj);
    }
    return obj;
}
