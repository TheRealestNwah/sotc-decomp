extern char rootPtn[];
extern const char RO_0017CCD0[];
extern char D_0017A3D8[];
extern int schedGarbageDisableFlag;
extern void DispLayoutObjModel(void);
extern void ClipLayoutObjModel(void);
extern void CalcLightLayoutObj(void);
extern void garbageNmoCallBack(void);
extern void *memset(void *, int, unsigned int);
extern void *CreateLayoutObj(void *, int, void *);
extern void isysResolveOneModuleObj(char *);
extern void modelInitialize(int, int, char *);
extern void EntrySeamlessStageObject(void *, int, int, int, int, int);
extern void iosMallocSetExecGarbageCallback(int, void (*)(void), char *);
extern void iosFree(void *);

static void func_00023450(int *req)
{
    char *root = rootPtn;
    const char *name = RO_0017CCD0;
    char *mod = *(char **)req;
    int model = *(int *)(mod + 0x20);
    char desc[0x7C];
    void *obj;

    memset(desc, 0, sizeof(desc));
    *(const char **)(desc + 0x0) = name;
    *(int *)(desc + 0x4) = 1;
    *(int *)(desc + 0x3C) = 6;
    *(void **)(desc + 0x60) = DispLayoutObjModel;
    *(void **)(desc + 0x68) = ClipLayoutObjModel;
    *(void **)(desc + 0x6C) = CalcLightLayoutObj;
    *(char **)(desc + 0x8) = mod;
    obj = CreateLayoutObj(root, 0, desc);
    isysResolveOneModuleObj(mod);
    modelInitialize(*(int *)mod, model, D_0017A3D8);
    if (obj != 0)
        EntrySeamlessStageObject(obj, req[2], req[4], req[5], req[6], req[3]);
    iosMallocSetExecGarbageCallback(*(int *)(mod + 0x1C), garbageNmoCallBack, mod);
    iosFree(req);
    schedGarbageDisableFlag--;
}
