extern float ZeroPoint[];
extern void CopyGeometryPointer(void *, char *);
extern void charrootdyn_updateCharacterClassParentGeometry(char *, float *, char *);
extern void charrootdyn_parentpointxzfitstab(char *, int, int);
extern void func_0006DFD0(void *, char *, void *, void *);

void motrootdyn_startxzfit_from_parentpointxzfit(void *m, char *c, void *p)
{
    char g[0x40] __attribute__((aligned(16)));
    CopyGeometryPointer(g, c + 0xC0);
    charrootdyn_updateCharacterClassParentGeometry(c, ZeroPoint, c + 0x6D0);
    charrootdyn_parentpointxzfitstab(c, *(int *)(c + 0x1C4), 0);
    func_0006DFD0(m, c, p, g);
}
