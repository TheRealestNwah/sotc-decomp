extern void func_0000ACF8();
extern char gcGlobalVar[];
extern char RO_0017C910[];
extern void *gcCreateScriptObj(void *, int, int, int, int, int, char *);

void *initgcchartest(void)
{
    return gcCreateScriptObj(func_0000ACF8, 0, *(int *)(gcGlobalVar + 0x308), 0x10000, 0, 1, RO_0017C910);
}
