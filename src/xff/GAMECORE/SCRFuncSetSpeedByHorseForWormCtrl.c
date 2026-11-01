extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern float getHorseInterpSpeed(void *);
extern void *getSCRDataCtrlWork(void *);
extern int execCondition(void *, int);
extern int setAttainSpeedWormCtrlWork(void *, float);

int SCRFuncSetSpeedByHorseForWormCtrl(void *actor, float minSpeed, float defSpeed, float scale,
                                       int a1, int a2, int a3, int t0, int t1, int cond)
{
    float speed;
    char *data;
    void *work;

    speed = getHorseInterpSpeed(SCRGetFirstObj(gcGlobalVar + 0x2B4));
    data = getSCRDataCtrlWork(actor);

    if (*(int *)(data + 0x4090) == 3) {
        work = data + 0x3D10;
        if (execCondition(actor, cond) && minSpeed <= speed)
            setAttainSpeedWormCtrlWork(work, speed * scale);
        else
            setAttainSpeedWormCtrlWork(work, defSpeed);
    }
}
