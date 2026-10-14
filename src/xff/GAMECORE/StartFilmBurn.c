extern void func_0004DD98();
extern char rootPtn[];
extern char RO_0017D300[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

void *StartFilmBurn(void)
{
    return gcCreateScriptObj(func_0004DD98, 0, rootPtn, 0x2000, 0, 8, RO_0017D300);
}
