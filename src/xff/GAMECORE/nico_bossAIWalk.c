extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern void SCRCharaTurn(void *, float);
extern void SCRCharaAccel(void *, float, int);
extern void SCRExecBossPostProcess(void *);
extern void scrRunM(int);

void nico_bossAIWalk(void **a)
{
    void *t = isysGetThisSubThread();
    void *o = *a;
    char *g = gcGlobalVar;
    for (;;) {
        SCRCharaTurn(t, 1.0f);
        SCRCharaAccel(t, *(float *)(g + 0x180), 10);
        SCRExecBossPostProcess(o);
        isysGetThisSubThread();
        scrRunM(1);
    }
}
