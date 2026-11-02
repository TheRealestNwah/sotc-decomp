extern void motrootdyn_parent_from_falldown();
extern int ParentLayoutObj(void *, char *);
extern void charrootdyn_getLocalOffsetFromParentGP(char *, void *, void *, char *);
extern void func_00069300(void *, void *, int);

void motrootdyn_startparentpointxzfit_from_falldown(void *actor, char *c, void *e)
{
    char *g = c + 0xC0;

    motrootdyn_parent_from_falldown();
    if (*(int *)(c + 0xFBC)) {
        ParentLayoutObj(actor, c + 0xF70);
    } else if (!*(int *)(c + 0x124) && *(int *)(c + 0xF3C)) {
        ParentLayoutObj(actor, c + 0xEF0);
    }
    charrootdyn_getLocalOffsetFromParentGP(c + 0x6D0, *(void **)(c + 0x13C), *(void **)(c + 0x134), g);
    func_00069300(actor, e, 0);
}
