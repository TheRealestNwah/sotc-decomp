extern char *GetSCRCharaAIWorkPtr(void *);

static void func_0007D588(void *obj)
{
    char *w = GetSCRCharaAIWorkPtr(obj);
    int v = *(int *)(w + 0x148);

    *(int *)(w + 0x148) = 0;
    *(int *)(w + 0x14C) = v;
}
