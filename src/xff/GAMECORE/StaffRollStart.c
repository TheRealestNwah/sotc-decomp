typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern int D_0017A84C;
extern unsigned char RO_0017CE08[];
extern void func_00025E00();
extern void *texSearchMopByName(void *);
extern void *createScriptObj(void *, void *, Ptn *, int, int, int, int, int);

void StaffRollStart(void)
{
    void *m;
    if (D_0017A84C != 0)
        return;
    m = texSearchMopByName(RO_0017CE08);
    createScriptObj(func_00025E00, m, &rootPtn, 0x2000, 0, 9, 0, 0);
}
