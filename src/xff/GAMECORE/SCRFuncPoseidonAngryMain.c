extern void *GetSCRCharaAIWorkPtr(void *);
extern unsigned char gcGlobalVar[];

union TimerValue {
    float value;
    int bits;
};

void SCRFuncPoseidonAngryMain(void *actor, int threshold, float timeout)
{
    float elapsed;
    void *work;

    work = GetSCRCharaAIWorkPtr(actor);
    if (*(int *)((char *)work + 0x41D0) >= threshold) {
        elapsed = ((union TimerValue *)((char *)work + 0x41DC))->value
                  + *(float *)(gcGlobalVar + 0x180);
        ((union TimerValue *)((char *)work + 0x41DC))->value = elapsed;
        if (timeout <= elapsed) {
            *(volatile int *)((char *)work + 0x41D0) = 0;
            ((volatile union TimerValue *)((char *)work + 0x41DC))->bits = 0;
        }
    }
}
