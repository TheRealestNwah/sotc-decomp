typedef struct { int a; int id; } Thr;
extern Thr *B_000516E0[];
extern unsigned char RO_00042730[];
extern int GetThreadId(void);
extern int WakeupThread(int);
extern void iosJumpRecoverPoint(void *);

void iosWakeupThread(Thr *t)
{
    if (t == 0)
        t = B_000516E0[GetThreadId()];
    if (WakeupThread(t->id) < 0)
        iosJumpRecoverPoint(RO_00042730);
}
