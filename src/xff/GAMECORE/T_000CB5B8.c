extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern void isysRequestDeleteObj(void *);

static int T_000CB5B8(void *p)
{
    void *o = SCRGetFirstObj(gcGlobalVar + 0x2B8);

    if (o && *(int *)(GetSCRCharaAIWorkPtr(o) + 0x41D8) == 0)
        isysRequestDeleteObj(p);
}
