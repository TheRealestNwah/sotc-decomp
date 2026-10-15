extern void func_001205F0();
extern char rootPtn[];
extern char RO_001816C8[];
extern void *_gcCreateChildScriptObj(void *, void *, void *, int, int, int, char *, void *);

void *createScrDemoManager(void *parent)
{
    return _gcCreateChildScriptObj(func_001205F0, parent, rootPtn, 0x4000, 0, 4, RO_001816C8, parent);
}
