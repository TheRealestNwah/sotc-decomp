extern void *getSCRDataCtrlWork(void *);
extern void setAcceleParamWormCtrlWork(void *, float, float);
extern int setAttainSpeedWormCtrlWork(float, void *);

void SCRFuncSetAcceleParamWormCtrlParam(void *actor, float speed, float first, float second)
{
    void *data;
    void *work;

    data = getSCRDataCtrlWork(actor);
    if (*(int *)((char *)data + 0x4090) == 3) {
        work = (char *)data + 0x3D10;
        setAttainSpeedWormCtrlWork(speed, work);
        setAcceleParamWormCtrlWork(work, first, second);
    }
}
