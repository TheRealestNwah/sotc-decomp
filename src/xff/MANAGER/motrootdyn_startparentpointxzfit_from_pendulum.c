typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;
extern void charrootdyn_updateCharacterClassParentGeometry(char *, s128 *, char *);
extern void *GetGeometryPointerSurfacePlane(char *);
extern void charrootdyn_getCompleteFittingYQFromYDir(void *, void *, void *);
extern void charrootdyn_parentpointxzfitstab(char *, int, int);

void motrootdyn_startparentpointxzfit_from_pendulum(void *a, char *c, int e)
{
    char *g = c + 0xC0;
    void *q = *(void **)(c + 0x13C);
    charrootdyn_updateCharacterClassParentGeometry(c, &ZeroPoint, c + 0xC10);
    charrootdyn_getCompleteFittingYQFromYDir(q, GetGeometryPointerSurfacePlane(g), q);
    charrootdyn_parentpointxzfitstab(c, *(int *)(c + 0x1C0), e);
}
