typedef struct Ptn Ptn;
typedef void *(*SheetTransform)(void *, int, int);
extern SheetTransform B_0015181C;
extern Ptn *B_00151820;
extern void T_000E1EC8(int, int);
extern void sheetFsLoadStageTex(int, void (*)(int, int), Ptn *);

void sheetFileLoadStageTex(int stage, Ptn *partition, SheetTransform transform)
{
    B_0015181C = transform;
    B_00151820 = partition;
    sheetFsLoadStageTex(stage, T_000E1EC8, partition);
}
