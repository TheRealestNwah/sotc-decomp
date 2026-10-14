extern void *GetSCRCharaAIWorkPtr(void *);
extern unsigned char gcGlobalVar[];

void SCRFuncKameCrackAnimMain(void *actor) {
    float temp_f1;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    temp_f1 = (*(float *)((char *)(temp_v0) + 0x41CC));
    if (temp_f1 > 0.0f) {
        (*(float *)((char *)(temp_v0) + 0x41CC)) = (float) (temp_f1 - (*(float *)((char *)(gcGlobalVar) + 0x180)));
    }
}
