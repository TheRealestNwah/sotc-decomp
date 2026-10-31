extern char *GetSCRCharaAIWorkPtr(void);
extern void isysRequestDeleteObj(void *);

static void T_000645F0(void)
{
    char *w = GetSCRCharaAIWorkPtr();

    if (*(int *)(w + 0x41C0) == 0) {
        isysRequestDeleteObj(*(void **)(w + 0x41B8));
        isysRequestDeleteObj(*(void **)(w + 0x41BC));
        isysRequestDeleteObj(*(void **)(w + 0x41B0));
        isysRequestDeleteObj(*(void **)(w + 0x41B4));
        *(int *)(w + 0x41C0) += 1;
    } else if (*(int *)(w + 0x41C0) == 1) {
        *(int *)(w + 0x41C0) = 2;
    }
}
