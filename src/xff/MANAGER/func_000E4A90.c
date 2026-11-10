/* Parked: 60 diffs (a3/a2 register choice for the table base). */
#ifdef NONMATCHING
typedef struct IsysObj {
    char pad0[0x3C];
    int f3C;
    int f40;
    unsigned f44;
    char pad48[0x10];
    int f58;
    int f5C;
} IsysObj;

extern int D_00139F10;
extern IsysObj *B_00151844;
extern char RO_00141CD8[];
extern char rootPtn[];
extern IsysObj *_isysCreateObj(char *, int, int, int, int, int);
extern void func_000E2808(int, int, IsysObj *);
extern void iosJumpRecoverPoint(char *, int, int);
extern int isysGetXffWorkSize(int);
extern void isysInitGroup(void *);
extern void isysResolveAllModuleObjHasUndefSymbol(void);

static IsysObj *func_000E4A90(int a0, int a1, int a2) {
    int s2;
    IsysObj *o;
    unsigned t;
    int *d;
    d = (int *)D_00139F10;
    s2 = d[a2];
    if (s2 == 0) iosJumpRecoverPoint(RO_00141CD8, a2, (int)d);
    o = _isysCreateObj(rootPtn, 5, 0x60, isysGetXffWorkSize(a0), 0, 8);
    o->f3C = s2;
    t = o->f44 & 0xC00FFFFF;
    o->f58 = 0;
    t &= 0xFFF7FFFF;
    o->f5C = 0;
    o->f44 = t;
    isysInitGroup((char *)o + 0x48);
    if (a0 != 0) func_000E2808(a0, a1, o);
    else o->f40 = 0;
    isysResolveAllModuleObjHasUndefSymbol();
    o->f44 = o->f44 | 0x80000;
    B_00151844 = o;
    return o;
}
#endif
