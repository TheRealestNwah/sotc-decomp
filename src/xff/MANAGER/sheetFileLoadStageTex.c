extern int B_0015181C;
extern int B_00151820;
extern char D_000E1EC8[];
extern void sheetFsLoadStageTex(int, void *, int);

void sheetFileLoadStageTex(int a, int b, int c)
{
    B_0015181C = c;
    B_00151820 = b;
    sheetFsLoadStageTex(a, D_000E1EC8, b);
}
