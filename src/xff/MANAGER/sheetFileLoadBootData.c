typedef struct Ptn Ptn;
extern void sheetFsLoadBootData(void (*cb)(int a, int b), Ptn *);
extern Ptn *B_00151820;
extern int B_0015182C;
extern int B_00151830;
extern int B_00151834;
extern void T_000E1AD0(int a, int b);

void sheetFileLoadBootData(Ptn *partition, int arg1, int arg2, int arg3)
{
    B_00151830 = arg1;
    B_0015182C = arg2;
    B_00151834 = arg3;
    B_00151820 = partition;
    sheetFsLoadBootData(&T_000E1AD0, partition);
}
