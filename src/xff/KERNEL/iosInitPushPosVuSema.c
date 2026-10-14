extern int B_000547F0;
extern int iosCreateSema(int, int, int);

void iosInitPushPosVuSema(void)
{
    B_000547F0 = iosCreateSema(1, 1, 0);
}
