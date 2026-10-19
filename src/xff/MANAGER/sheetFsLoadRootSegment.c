typedef struct Ptn Ptn;
extern int B_001517D0;
extern void iosCdStStart(int);
extern void iosCdStStop(void);

void sheetFsLoadRootSegment(void (*cb)(int, int), Ptn *unusedPartition)
{
    iosCdStStart(B_001517D0);
    cb(0, 0);
    iosCdStStop();
}
