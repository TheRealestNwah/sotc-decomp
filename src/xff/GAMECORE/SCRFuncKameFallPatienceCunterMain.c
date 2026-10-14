extern void *GetSCRCharaAIWorkPtr(void *);
extern unsigned char gcGlobalVar[];

void SCRFuncKameFallPatienceCunterMain(void *actor) {
    float temp_f1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    temp_f1 = (*(float *)((char *)(temp_v0) + 0x41C0));
    if (temp_f1 > 0.0f) {
        (*(float *)((char *)(temp_v0) + 0x41C0)) = (float) (temp_f1 - (*(float *)((char *)(gcGlobalVar) + 0x180)));
    }
}
