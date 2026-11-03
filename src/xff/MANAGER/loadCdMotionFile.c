#ifdef NONMATCHING /* 4 instruction diffs: v0/v1 swapped on the 0x40000000 flags test after isysAddGroupWithLinkParam (same as loadCdXffFile); everything else matches */
typedef struct Ptn Ptn;
typedef struct {
    char pad[0x2C];
    unsigned int flags;
} ModObj;
typedef struct {
    char pad[0xC];
    ModObj *obj;
} SheetData;
extern Ptn rootPtn;
extern int D_00136C10;
extern char B_001498C0[];
extern void *iosMallocInGarbagePtn(int, int);
extern void vschedSetNextFrameForceGarbage(void);
extern void sheetWait(void);
extern void sheetFileRead(void *, void *, int);
extern ModObj *isysCreateModuleObjExisted(void *, int, void *, int, int, int, void *);
extern void isysAddGroupWithLinkParam(ModObj *, int, int, int);
extern void iosJumpRecoverPoint(const char *);
extern SheetData *sheetFileGetDataAdrs(void *);
static inline ModObj *createObj(void *buffer, int work, Ptn *ptn, int garbage)
{
    return isysCreateModuleObjExisted(buffer, work, ptn, 1, 0, 1, garbage ? 0 : ptn);
}
ModObj *loadCdMotionFile(void *file, int unused, int size)
{
    void *buffer;
    ModObj *obj;
    SheetData *data;
    Ptn *ptn = &rootPtn;
    int garbage = 0;
    while ((buffer = iosMallocInGarbagePtn(size, 16)) == 0) {
        vschedSetNextFrameForceGarbage();
        sheetWait();
    }
    sheetFileRead(file, buffer, size);
    obj = createObj(buffer, 0, ptn, garbage);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, D_00136C10, 0, 0);
        if (!(obj->flags & 0x40000000)) {
            iosJumpRecoverPoint("objman:\t\272\306\307\333\303\326\311\324\307\275\262\275\274\272\307\324\n");
        }
    }
    data = sheetFileGetDataAdrs(file);
    if (obj != 0) {
        *(unsigned int *)B_001498C0 += size;
    }
    data->obj = obj;
    return obj;
}
#endif
