extern char B_0019B868[];
extern void isysInitGroup(void *);
extern void func_000965E8();
extern char rootPtn[];
extern char RO_0017F8D8[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

void *initdefaultaitask(void)
{
    isysInitGroup(B_0019B868);
    return gcCreateScriptObj(func_000965E8, 0, rootPtn, 0x1000, 0, 4, RO_0017F8D8);
}
