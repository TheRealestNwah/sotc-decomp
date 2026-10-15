extern void sheetFsLoadRootSegment(void (*cb)(int a, int b), int);
extern int B_0015181C;
extern int B_00151820;
extern void D_000E1EB0(int a, int b);

void sheetFileLoadRootSegment(int arg0, int arg1)
{
    B_0015181C = arg1;
    B_00151820 = arg0;
    sheetFsLoadRootSegment(D_000E1EB0, arg0);
}
