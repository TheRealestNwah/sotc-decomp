extern int IosGetMergeDataFileName();
extern void func_000DFEB0();
extern void iosCdStInit(int);

void sheetFsInit(void)
{
    iosCdStInit(IosGetMergeDataFileName());
    func_000DFEB0();
}
