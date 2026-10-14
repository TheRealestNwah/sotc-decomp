extern int B_000C3950;
extern int iosCreateSema(int, int, int);

void InitIopDev(void)
{
    B_000C3950 = iosCreateSema(1, 1, 0);
}
