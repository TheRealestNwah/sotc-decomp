extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncYamoriBSetBreathVolume(void *actor, int a, int b, int c, int d, int e, int volume)
{
    *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x41CC) = volume;
}
