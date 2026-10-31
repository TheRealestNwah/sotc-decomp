extern char *GetSCRCharaAIWorkPtr(void *);
extern void _SCRStartLWS(int, int, int, int);

static void func_00035438(void *obj)
{
    _SCRStartLWS(*(int *)(GetSCRCharaAIWorkPtr(obj) + 0x41B0), -1, 1, 0);
}
