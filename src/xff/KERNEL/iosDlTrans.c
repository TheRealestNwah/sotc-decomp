typedef struct { int a, b; int adrs[2]; int ptr; int e; int cur; } DlBufs;

extern int B_00065010;
extern DlBufs B_00065018;
extern int D_00040AF4;
extern void WaitSema(int sema);
extern void SignalSema(int sema);
extern void iosDmaSendSChainPath1(int adrs);

/* Sends the display list that is not being built, under the DL semaphore. */
void iosDlTrans(void)
{
    volatile int *sema = &B_00065010;
    volatile DlBufs *dl;
    volatile int *count;
    int s;

    WaitSema(*sema);
    dl = &B_00065018;
    iosDmaSendSChainPath1(dl->adrs[dl->cur == 0]);
    count = &D_00040AF4;
    s = *sema;
    (*count)++;
    SignalSema(s);
}
