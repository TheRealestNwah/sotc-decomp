extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern int CheckSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern int *GetAnimationClass(void *);

int SCRConditionBossDeathLoopMotion(void)
{
    int none;
    void *obj;
    char *work;

    obj = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    if (obj != 0) {
        none = CheckSCRCharaAIWorkPtr(obj) == 0;
        if (none) {
            return 0;
        }
        work = getSCRDataCtrlWork(obj);
        if (*GetAnimationClass(obj) == *(int *)(work + 0x4160)) {
            return 1;
        }
    }
    return 0;
}
