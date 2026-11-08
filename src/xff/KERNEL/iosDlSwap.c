typedef struct {
    char pad0[0x18];
    volatile int flip;
    char pad1C[4];
    int group[2];
    volatile int count[2];
} PathState;

extern volatile int B_00065010;
extern PathState B_00065018;
extern int WaitSema(int);
extern int SignalSema(int);
extern void isysObjWaitSema(void);
extern void isysObjSignalSema(void);
extern int *isysGroupForFirstForce(void *, int);
extern int *isysGroupForNextForce(int *, int);
extern void isysGroupForExit(void *, int);
extern void isysObjDeleteUnLock(int);
extern void isysDeleteGroupAllObj(void *);
extern void func_00012C30(void);

void iosDlSwap(void)
{
    int last = 0;
    int idx;
    int *grp;
    int *it;

    WaitSema(B_00065010);
    B_00065018.flip ^= 1;
    idx = B_00065018.flip;
    grp = &B_00065018.group[idx];
    isysObjWaitSema();
    for (it = isysGroupForFirstForce(grp, 0); it; it = isysGroupForNextForce(it, 0)) {
        last = *it;
        isysObjDeleteUnLock(last);
        B_00065018.count[idx]--;
    }
    if (last)
        isysGroupForExit((void *)last, 0);
    isysDeleteGroupAllObj(grp);
    isysObjSignalSema();
    func_00012C30();
    SignalSema(B_00065010);
}
