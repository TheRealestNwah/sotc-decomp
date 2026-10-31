extern char *GetSCRCharaAIWorkPtr(void);
extern void nico_getOmakeItem(int, void *);

static void T_0007D5E8(void *p)
{
    char *w = GetSCRCharaAIWorkPtr();

    nico_getOmakeItem(*(int *)(w + 0x14C), p);
    *(int *)(w + 0x148) = 0;
    *(int *)(w + 0x14C) = 0;
}
