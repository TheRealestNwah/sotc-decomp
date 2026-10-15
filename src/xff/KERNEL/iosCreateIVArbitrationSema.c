extern int B_00065010;
extern int iosCreateSema(int a, int b, int c);

void iosCreateIVArbitrationSema(void)
{
    int s = iosCreateSema(0, 1, 0);
    volatile int *p = &B_00065010;

    *p = s;
}
