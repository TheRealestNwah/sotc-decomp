extern int D_0017A868;
extern int D_0017A86C;
extern int B_00188668[5];
extern int B_00188650[5];
extern int B_00188738[5];
extern char B_00188730[];
extern char rootPtn[];
extern char RO_0017CE30[];
extern void isysInitGroup(void *);
extern void func_0002BAB8(int, int);
extern void func_0002B2B0(void);
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);

static inline void fillNeg(int *p, int v)
{
    int i;

    for (i = 4; i >= 0; i--)
        *p++ = v;
}

void *CreateStageManager(int arg)
{
    D_0017A868 = 0;
    D_0017A86C = 0;
    fillNeg(B_00188668, -1);
    fillNeg(B_00188650, -1);
    fillNeg(B_00188738, -1);
    isysInitGroup(B_00188730);
    func_0002BAB8(-1, 0);
    return gcCreateScriptObj(func_0002B2B0, 0, rootPtn, 0x1800, 0, arg, RO_0017CE30);
}
