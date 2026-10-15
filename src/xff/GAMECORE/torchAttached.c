extern void *GetSCRCharaAIWorkPtr(void *);
extern unsigned char gcGlobalVar[];

void torchAttached(void *actor, float fparg0)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    if ((*(int *)((char *)(temp_v0) + 0x70)) == 9) {
        (*(float *)((char *)(temp_v0) + 0x84)) = fparg0;
        (*(signed char *)((char *)(temp_v0) + 0x95)) = 0;
        (*(float *)((char *)(temp_v0) + 0x88)) = (float) (*(float *)((char *)(gcGlobalVar) + 0x180));
    }
}
