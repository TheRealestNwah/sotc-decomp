extern int D_00040D60;
extern int D_00040D5C;
extern int B_000BF6CC;
extern void SignalSema(int);

void isysObjSignalSema(void)
{
    int *p = &D_00040D60;
    if (--*p == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}
