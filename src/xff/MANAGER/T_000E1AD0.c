extern void sheetFsDataRead(void *, void *, int);
extern void *iosMallocAlign(void *, int, int);
extern void *B_00151820;
extern void (*B_0015182C)(void *, int, int);
extern void (*B_00151830)(void *, int, int);
extern void (*B_00151834)(void *, int);
extern int D_00139F08;

#ifdef NONMATCHING
/* 11 diffs: jalr target registers and argument setup order */
static void T_000E1AD0(void *fs)
{
    int size0;
    int size1;
    int count;
    int nameLen;
    int size2;
    void *p0;
    void *p;
    int i;

    i = 0;
    sheetFsDataRead(fs, &size0, 4);
    p = iosMallocAlign(B_00151820, size0, 0x10);
    p0 = p;
    sheetFsDataRead(fs, p, size0);
    sheetFsDataRead(fs, &size1, 4);
    p = iosMallocAlign(B_00151820, size1, 0x10);
    sheetFsDataRead(fs, p, size1);
    sheetFsDataRead(fs, &count, 4);
    B_00151830(p0, 0, count);
    B_0015182C(p, size1, 0);
    for (; i < count; i++) {
        sheetFsDataRead(fs, &nameLen, 4);
        sheetFsDataRead(fs, &size2, 4);
        {
            char name[nameLen];
            sheetFsDataRead(fs, name, nameLen);
            p = iosMallocAlign(B_00151820, size2, 0x10);
            sheetFsDataRead(fs, p, size2);
            B_00151834(p, D_00139F08++);
        }
    }
}
#endif
