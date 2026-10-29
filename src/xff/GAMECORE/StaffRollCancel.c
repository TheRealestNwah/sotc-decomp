extern int D_0017A84C;
extern void fadeOut(int, int, float);

void StaffRollCancel(void)
{
    D_0017A84C = 0;
    fadeOut(0, 0, 3.0f);
}
