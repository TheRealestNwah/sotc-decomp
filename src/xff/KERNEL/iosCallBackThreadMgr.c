typedef struct { int a; int id; } Thr;
extern int B_00053B04;
extern int B_00053B00;
extern void *B_00053AF8;
extern void *B_00053AFC;
extern Thr *B_00053AF0;
extern void WaitSema(int);
extern int WakeupThread(int);

int iosCallBackThreadMgr(void *a, void *b)
{
    WaitSema(B_00053B04);
    B_00053B00 = 1;
    B_00053AF8 = a;
    B_00053AFC = b;
    return WakeupThread(B_00053AF0->id);
}
