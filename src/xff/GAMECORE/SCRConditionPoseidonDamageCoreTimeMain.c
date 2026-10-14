extern void *GetSCRCharaAIWorkPtr(void *);
extern unsigned char gcGlobalVar[];

void SCRConditionPoseidonDamageCoreTimeMain(void *actor) {
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    if ((*(int *)((char *)(temp_v0) + 0x41BC)) != 0) {
        (*(float *)((char *)(temp_v0) + 0x41D8)) = (float) ((*(float *)((char *)(temp_v0) + 0x41D8)) + (*(float *)((char *)(gcGlobalVar) + 0x180)));
    }
}
