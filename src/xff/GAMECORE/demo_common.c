extern char rootPtn[], gcGlobalVar[], SH_StageDataDEFAULT[];
extern void *DldSysUndefSymbol;
extern int isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptLayoutClass(int);
extern void SetScriptLayoutObjLetterProcMode(int, int);
extern char *_SCRMallocAlign(char *, int, int);
extern void *memset(void *, int, unsigned int);
extern void scrRun(void);
extern int stagemanager_getStageNumberWithStageDataStrptr(char *);
extern int sheetMgrLoadSegmentIndex(char *, int, int *);
extern int sheetMgrUnloadSegmentIndex(char *, int, int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void ischedStop(void);
extern void ischedRestart(void);
extern void DelayThread(int);
extern void func_000D3F00(int *, int);
extern float func_000D3D60(char *, int *);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        return *(char **)(module + 0x10) + index * *(int *)(*(char **)(module + 8) + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING /* 254 diffs, 274 vs 272 words: jump-table switch layout and loop-carried float/pointer registers; transitions reconstructed from the jump table (cases 0-5, default = no-op) */
void demo_common(void)
{
    int sp[2];
    int s2 = isysGetThisSubThread();
    char *s0, *s1;
    int *w;
    int k;
    float step;

    iosCreatePartition(rootPtn, 0x87);
    s0 = GetScriptLayoutClass(s2);
    *(char **)(GetScriptLayoutClass(s2) + 0x2D4) = s0;
    SetScriptLayoutObjLetterProcMode(s2, 1);
    s1 = GetScriptLayoutClass(s2);
    w = (int *)_SCRMallocAlign(s0, 0x54, 0x10);
    *(int **)(s1 + 0x2D8) = w;
    memset(w, 0, 0x54);
    while (w[1] == 0)
        scrRun();
    func_000D3F00(w, s2);
    w[2] = 1;
    while (w[3] == 0)
        scrRun();
    k = 0;
    w[0] = 0;
    while (w[4] == 0) {
        float cur = *(float *)((char *)w + 0x3C);
        char *src = (char *)w[0x48 / 4];
        float prev = *(float *)((char *)w + 0x3C);
        *(float *)((char *)w + 0x3C) = *(float *)(src + 0x3C);
        step = (*(float *)(src + 0x3C) - prev) / 30.0f;
        w[0x4C / 4] = *(int *)(src + 0x40);
        switch (w[0]) {
        case 0:
            w[0x2C / 4] = stagemanager_getStageNumberWithStageDataStrptr((char *)w[0x1C / 4] + 0x10);
            if (w[0x2C / 4] > 0) {
                sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, w[0x2C / 4], sp);
                w[0] = 1;
            } else {
                w[0] = 6;
            }
            break;
        case 1:
            if ((unsigned)(sp[0] + 0xFFFF2151) < 2) {
                float v = func_000D3D60(resourceData((unsigned int *)((char *)w[0x1C / 4] + 8)), &sp[1]);
                *(float *)((char *)w + 0x30) = v;
                *(float *)((char *)w + 0x40) = *(float *)((char *)w + 0x40) + v;
                w[0x44 / 4] += 1;
                w[0x50 / 4] += sp[1];
                w[0] = 2;
            } else if (*(float *)((char *)w + 0x28) <= *(float *)((char *)w + 0x24) + 1.0f) {
                PauseGame(1);
                if ((unsigned)(sp[0] + 0xFFFF2151) >= 2) {
                    do {
                        ischedStop();
                        DelayThread(1000000);
                        ischedRestart();
                    } while ((unsigned)(sp[0] + 0xFFFF2151) >= 2);
                }
                ReleaseGame(1);
            }
            break;
        case 2:
            break;
        case 3:
            k = 0;
            w[0] = 4;
            break;
        case 4:
            if (k++ >= 3)
                w[0] = 5;
            break;
        case 5:
            sheetMgrUnloadSegmentIndex(SH_StageDataDEFAULT, w[0x2C / 4], 0);
            w[0x2C / 4] = 0;
            w[0] = 0;
            break;
        default:
            break;
        }
        *(float *)((char *)w + 0x24) += step;
        *(float *)((char *)w + 0x34) += step;
        *(float *)((char *)w + 0x38) += *(float *)(gcGlobalVar + 0x180);
        if (*(float *)((char *)w + 0x28) <= *(float *)((char *)w + 0x24)) {
            if (w[0] == 2 || w[0] == 6) {
                if (w[0] == 2) {
                    char *p = resourceData((unsigned int *)((char *)w[0x1C / 4] + 8));
                    int t = w[0x20 / 4];
                    w[0x20 / 4] = w[0x2C / 4];
                    w[0x2C / 4] = t;
                    w[0x1C / 4] = (int)p;
                    *(float *)((char *)w + 0x24) -= *(float *)((char *)w + 0x28);
                    *(float *)((char *)w + 0x28) = *(float *)((char *)w + 0x30);
                    w[0] = 3;
                } else {
                    w[4] = 1;
                }
            }
        }
        scrRun();
    }
}
#endif
