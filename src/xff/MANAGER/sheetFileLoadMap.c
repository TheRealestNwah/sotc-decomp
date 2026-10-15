extern int B_0015181C;
extern int B_00151820;
extern int B_00151824;
extern int B_00151828;
extern void T_000E1870();
extern void sheetFsLoadMap(int, int, int, int, int, void *, int);

void sheetFileLoadMap(int a, int b, int c, int d, int e, int f, int g)
{
    B_0015181C = g;
    B_00151820 = f;
    B_00151824 = b;
    B_00151828 = e;
    sheetFsLoadMap(a, b, c, d, e, T_000E1870, f);
}
