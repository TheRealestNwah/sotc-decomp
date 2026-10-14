extern int GetThreadId();
extern void WaitSema(int);
extern int B_000BF6CC;
extern int D_00040D5C;
extern int D_00040D60;

void isysObjWaitSema(void)
{
    int temp_v0;

    temp_v0 = GetThreadId();
    if (temp_v0 == D_00040D5C) {
        D_00040D60 += 1;
        return;
    }
    WaitSema(B_000BF6CC);
    D_00040D5C = temp_v0;
    D_00040D60 = 1;
}
