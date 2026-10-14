extern void st_stageboundary();
extern char rootPtn[];
extern char RO_0017CE80[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

void *CreateStageBoundaryManager(int arg)
{
    return gcCreateScriptObj(st_stageboundary, 0, rootPtn, 0x2000, 0, arg, RO_0017CE80);
}
