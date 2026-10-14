extern void *GetSCRCharaAIWorkPtr(void *);
extern void isysRequestDeleteObj(int);

void torchObjRelease(void *actor) {
    int temp_v0_2;
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    temp_v0_2 = (*(int *)((char *)(temp_v0) + 0x150));
    if (temp_v0_2 != 0) {
        isysRequestDeleteObj(temp_v0_2);
    }
    (*(int *)((char *)(temp_v0) + 0x150)) = 0;
}
