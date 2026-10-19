typedef struct Ptn Ptn;
typedef void *(*SheetTransform)(void *, int, int);
extern SheetTransform B_0015181C;
extern Ptn *B_00151820;
extern int B_00151824;
extern int B_00151828;
extern void T_000E1870(int, int);
extern void sheetFsLoadMap(int, int, int, int, int, void (*)(int, int), Ptn *);

void sheetFileLoadMap(int a, int b, int c, int d, int e, Ptn *partition, SheetTransform transform)
{
    B_0015181C = transform;
    B_00151820 = partition;
    B_00151824 = b;
    B_00151828 = e;
    sheetFsLoadMap(a, b, c, d, e, T_000E1870, partition);
}
