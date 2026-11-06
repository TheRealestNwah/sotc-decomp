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
extern int modelGetWorkSize(void *);
/* modelInitialize returns int; declaring it void changes the register for the next load. */
extern int modelInitialize(void *, void *, void *);
extern int garbageNmoCallBack();
extern int DldSysUndefSymbol;

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline ModObj *createObj(void *buffer, int work, Ptn *ptn, int garbage)
{
    ModObj *obj = isysCreateModuleObjExisted(buffer, work, ptn, 1, 0, 1, garbage ? 0 : ptn);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, D_00136C10, 0, 0);
    }
    return obj;
}

ModObj *loadCdNmoFile(void *file, int unused, int size)
{
    char *data = sheetFileGetDataAdrs(file);
    Ptn *ptn = *(Ptn **)(resourceData((unsigned int *)(data + 0x10)) + 8);
    int garbage = garbageNmoCallBack != 0;
    int work = 0;
    void *getWork;
    void *buffer;
    ModObj *obj;
    getWork = modelGetWorkSize;

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
        work = modelGetWorkSize(isysGetXffEntryPointPreRelocation(buffer));
    }
    obj = createObj(buffer, work, ptn, garbage);
    if (obj != 0) {
        void *objWork = obj->work;
        B_001498C0[5] += size;
        isysResolveOneModuleObj(obj);
        modelInitialize(obj->model, objWork, data);
        isysAddGroupWithLinkParam(obj, D_00136C10 + 4, 0, 0);
        iosMallocSetExecGarbageCallback(obj->mem, garbageNmoCallBack, obj);
    }
    return obj;
}
