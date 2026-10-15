extern void sheetFsLoadRootSegment(void *, int);
extern int B_0015181C;
extern int B_00151820;
extern unsigned char D_000E1EB0[];

void sheetFileLoadRootSegment(int arg0, int arg1)
{
    B_0015181C = arg1;
    B_00151820 = arg0;
    sheetFsLoadRootSegment(D_000E1EB0, arg0);
}
