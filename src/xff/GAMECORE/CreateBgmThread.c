extern void *adpcmScriptTickProc;
extern void func_000306C0();
extern char B_001888E8[];
extern void *memset(void *, int, unsigned int);

int CreateBgmThread(void)
{
    adpcmScriptTickProc = func_000306C0;
    memset(B_001888E8, 0, 0x9C);
    return 0;
}
