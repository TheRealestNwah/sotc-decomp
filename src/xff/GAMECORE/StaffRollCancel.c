extern int D_0017A84C;
extern int fadeOut(int, int, float);

int StaffRollCancel(void)
{
    D_0017A84C = 0;
    return fadeOut(0, 0, 3.0f);
}
