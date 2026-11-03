typedef struct Ptn Ptn;
typedef struct {
    char pad[0x1C];
    void *mem;
    void *res;
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
extern int IsClusterCollision(void *);
extern int garbageColResCallBack();

ModObj *loadCdColResFile(void *file, int unused, int size)
{
    Ptn *ptn = &rootPtn;
    int garbage = garbageColResCallBack != 0;
    void *buffer;
    ModObj *obj;

    if (garbage) {
        while ((buffer = iosMallocInGarbagePtn(size, 16)) == 0) {
            vschedSetNextFrameForceGarbage();
            sheetWait();
        }
    } else {
        buffer = iosMallocAlign(ptn, size, 16);
    }
    sheetFileRead(file, buffer, size);
    obj = isysCreateModuleObjExisted(buffer, 0, ptn, 1, 0, 1, garbage ? 0 : ptn);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, D_00136C10, 0, 0);
    }
    sheetFileGetDataAdrs(file);
    if (obj != 0) {
        iosMallocSetExecGarbageCallback(obj->mem, garbageColResCallBack, obj);
        if (IsClusterCollision(obj->res)) {
            B_001498C0[1] += size;
        } else {
            B_001498C0[3] += size;
        }
    }
    return obj;
}
