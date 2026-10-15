extern int B_00053B04;
extern int B_000516E0[];
extern int B_00053AF4, B_00053B00;
extern int *B_00053AF0;
extern int WaitSema(int sema);
extern int GetThreadId(void);
extern int WakeupThread(int tid);
int iosDeleteThread(int tid)
{
    WaitSema(B_00053B04);
    if (tid == 0) {
        tid = B_000516E0[GetThreadId()];
    }
    B_00053B00 = 0;
    B_00053AF4 = tid;
    return WakeupThread(B_00053AF0[1]);
}
