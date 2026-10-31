extern char *GetSCRCharaAIWorkPtr(void);
extern void dischargeTerm(int);
extern void unloadObj(int);

static void func_000CC7F8(void)
{
    int *obj = (int *)(GetSCRCharaAIWorkPtr() + 0x5AA4);
    int i;

    for (i = 2; i >= 0; i--) {
        dischargeTerm(*obj);
        unloadObj(*obj++);
    }
}
