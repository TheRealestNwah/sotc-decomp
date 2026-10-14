extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncKameSetMissileRadius(void *actor, float r0, float r1, float r2, float r3)
{
    char *work = GetSCRCharaAIWorkPtr(actor);

    if (r0 != 0.0f) {
        *(int *)(work + 0x41C4) = 0;
    } else if (r1 != 0.0f) {
        *(int *)(work + 0x41C4) = 1;
    } else if (r2 != 0.0f) {
        *(int *)(work + 0x41C4) = 2;
    } else if (r3 != 0.0f) {
        *(int *)(work + 0x41C4) = 3;
    }
}
