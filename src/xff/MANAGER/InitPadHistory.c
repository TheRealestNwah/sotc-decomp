extern int iosCreateSema(int a, int b, int c);

extern int B_0014DC0C;

void InitPadHistory(void)
{
    B_0014DC0C = iosCreateSema(1, 1, 0);
}
