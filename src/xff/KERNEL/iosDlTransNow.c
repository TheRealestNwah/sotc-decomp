typedef struct { int a, b; int chain[2]; int c, d; int cur; } DlState;
extern volatile int B_00065010;
extern volatile DlState B_00065018;
extern void WaitSema(int);
extern void SignalSema(int);
extern void iosDmaSendSChainPath1(int);

void iosDlTransNow(void)
{
    WaitSema(B_00065010);
    iosDmaSendSChainPath1(B_00065018.chain[B_00065018.cur == 0]);
    SignalSema(B_00065010);
}
