typedef struct Ptn Ptn;
extern int B_001517C8;
extern void iosCdStStart(int);
extern void iosCdStStop(void);

void sheetFsLoadBootData(void (*cb)(int, int), Ptn *unusedPartition)
{
    iosCdStStart(B_001517C8);
    cb(0, 0);
    iosCdStStop();
}
