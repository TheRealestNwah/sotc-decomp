typedef struct Ptn Ptn;
typedef void *(*SheetTransform)(void *, int, int);
extern SheetTransform B_0015181C;
extern Ptn *B_00151820;
extern void func_000E1E98(int, int);
extern void sheetFsLoadSegmentIndex(int, int, int, void (*)(int, int), Ptn *);

typedef struct {
    int id;
    int pad;
    int *archive;
} SheetFile;

void sheetFileLoadSegmentIndex(SheetFile *file, int index, Ptn *partition, SheetTransform transform)
{
    int *archive = file->archive;

    B_0015181C = transform;
    B_00151820 = partition;
    sheetFsLoadSegmentIndex(*archive, file->id, index, func_000E1E98, partition);
}
