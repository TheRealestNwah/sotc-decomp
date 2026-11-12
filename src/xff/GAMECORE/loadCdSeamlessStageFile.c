/* loadCdSeamlessStageFile: parked draft (~199 diffs; original is ~28 words longer: index calc compiles to movz here, explicit branches there) */
extern char D_0017A340[];
extern char D_0017A3AC[];
extern int D_0017A3D0;
extern int *D_0017A3D4;
extern char gcGlobalVar[];
extern char rootPtn[];
extern int schedGarbageDisableFlag;
extern void T_0001F8E8(void);
extern void func_00023450(void);
extern void createScriptObj(void *, void *, int, int);
extern void func_0001F838(int, int);
extern int *iosMallocAlign(void *, int, int);
extern int iosMallocInGarbagePtn(int, int);
extern void isysAddGroupWithLinkParam(int, void *, int, int);
extern int isysCreateModuleObjExisted(int, int, void *, int);
extern int isysGetXffEntryPointPreRelocation(int);
extern void isysResolveOneModuleObj(int);
extern int modelGetWorkSize(int);
extern void sheetFileRead(int, int, int);
extern void sheetWait(void);
extern void vschedSetNextFrameForceGarbage(void);

#ifdef NONMATCHING
int loadCdSeamlessStageFile(int file, int mode, int arg2, int size, int x, int y, int z)
{
    int idx;
    int buf;
    int mod;
    int *p;
    char *e;

    if (mode == 0) {
        idx = -1;
        if (x >= 0 && x < *(int *)(D_0017A340 + 0x48) && y >= 0) {
            idx = y * *(int *)(D_0017A340 + 0x48) + x;
            if (y >= *(int *)(D_0017A340 + 0x4C))
                idx = -1;
        }
        p = iosMallocAlign(rootPtn, 0x10, 0x10);
        p[2] = 5;
        p[0] = z;
        p[1] = idx;
        e = (char *)(idx * 0x18 + *(int *)(D_0017A340 + 8) + z * 4);
        *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 4;
        createScriptObj(T_0001F8E8, p, *(int *)(gcGlobalVar + 0x308), 0x1000);
        func_0001F838(x, y);
        return 0;
    }
    for (;;) {
        buf = iosMallocInGarbagePtn(size, 0x80);
        if (buf != 0)
            break;
        vschedSetNextFrameForceGarbage();
        sheetWait();
    }
    sheetFileRead(file, buf, size);
    mod = isysCreateModuleObjExisted(buf, modelGetWorkSize(isysGetXffEntryPointPreRelocation(buf)), rootPtn, 1);
    if (mod != 0) {
        isysResolveOneModuleObj(mod);
        isysAddGroupWithLinkParam(mod, D_0017A3AC, 0, 0);
        isysAddGroupWithLinkParam(mod, gcGlobalVar + 0x1CC, 0, 0);
        p = iosMallocAlign(rootPtn, 0x1C, 4);
        p[1] = mode;
        p[3] = size;
        p[2] = arg2;
        p[4] = x;
        p[5] = y;
        p[6] = z;
        p[0] = mod;
        schedGarbageDisableFlag += 1;
        createScriptObj(func_00023450, p, *(int *)(gcGlobalVar + 0x308), 0x1000);
    } else {
        idx = -1;
        if (x >= 0) {
            if (x < *(int *)(D_0017A340 + 0x48)) {
                if (y >= 0) {
                    idx = y * *(int *)(D_0017A340 + 0x48) + x;
                    if (y >= *(int *)(D_0017A340 + 0x4C))
                        idx = -1;
                }
            }
        }
        p = iosMallocAlign(rootPtn, 0x1C, 0x10);
        p[0] = x;
        p[1] = y;
        p[2] = z;
        p[3] = 0;
        p[4] = 0;
        p[5] = 0;
        p[6] = (int)D_0017A3D4;
        if (D_0017A3D4 != 0)
            D_0017A3D4[5] = (int)p;
        e = (char *)(idx * 0x18 + *(int *)(D_0017A340 + 8) + z * 4);
        D_0017A3D0 += 1;
        D_0017A3D4 = p;
        *(int **)e = p;
        *(int *)(e + 8) &= 0xF;
        *(int *)(e + 8) = (*(int *)(e + 8) & ~0xF) | 6;
    }
    return mod;
}
#endif
