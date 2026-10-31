extern char *GetSCRCharaAIWorkPtr(void);
extern void isysRequestDeleteObj(void *);

static void T_000CB598(void)
{
    isysRequestDeleteObj(*(void **)(GetSCRCharaAIWorkPtr() + 0x41D0));
}
