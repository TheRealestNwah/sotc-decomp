extern void func_000677B8(char *, int);
extern void charrootdyn_getLocalOffsetFromParentGP(char *, int, int, char *);

void motrootdyn_setupedgepoint(char *m)
{
    func_000677B8(m, 0);
    charrootdyn_getLocalOffsetFromParentGP(m + 0x6D0, *(int *)(m + 0x13C), *(int *)(m + 0x134), m + 0xC0);
}
