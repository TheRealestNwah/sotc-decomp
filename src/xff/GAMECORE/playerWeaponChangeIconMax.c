extern void *GetSCRCharaAIWorkPtr(void *);
extern void *SCRGetFirstObj(void *);
extern unsigned char gcGlobalVar[];

void playerWeaponChangeIconMax(void) {
    void *temp_v0;

    temp_v0 = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    if (temp_v0 != 0) {
        (*(int *)((char *)(GetSCRCharaAIWorkPtr(temp_v0)) + 0x80)) = 1;
    }
}
