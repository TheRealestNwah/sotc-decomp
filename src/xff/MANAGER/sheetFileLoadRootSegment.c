typedef struct Ptn Ptn;
typedef void *(*SheetTransform)(void *, int, int);
extern void sheetFsLoadRootSegment(void (*cb)(int a, int b), Ptn *);
extern SheetTransform B_0015181C;
extern Ptn *B_00151820;
extern void D_000E1EB0(int a, int b);

void sheetFileLoadRootSegment(Ptn *partition, SheetTransform transform)
{
    B_0015181C = transform;
    B_00151820 = partition;
    sheetFsLoadRootSegment(D_000E1EB0, partition);
}
