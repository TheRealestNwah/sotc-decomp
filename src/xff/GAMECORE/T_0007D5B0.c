extern char *GetSCRCharaAIWorkPtr(void);
extern void nico_setOmakeItemFlag(int, void *);

static void T_0007D5B0(void *p)
{
    char *w = GetSCRCharaAIWorkPtr();
    int v = *(int *)(w + 0x148);

    *(int *)(w + 0x148) = 0;
    *(int *)(w + 0x14C) = v;
    nico_setOmakeItemFlag(v, p);
}
