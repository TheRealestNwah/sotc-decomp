extern float ZeroPoint[];
extern void charrootdyn_updateCharacterClassParentGeometry(char *, float *, char *);
extern void motrootdyn_changehcol_from_xz(void *);
extern void func_00069300(void *, void *, int);

void motrootdyn_startparentpointxzfit_from_xz(void *m, char *c, void *p)
{
    charrootdyn_updateCharacterClassParentGeometry(c, ZeroPoint, c + 0x6D0);
    motrootdyn_changehcol_from_xz(m);
    func_00069300(m, p, 0);
}
