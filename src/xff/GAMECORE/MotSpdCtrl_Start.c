extern int MotSpdCtrl_StartExt(int, int, int, int, float);

int MotSpdCtrl_Start(int a, int b, int c, int d)
{
    return MotSpdCtrl_StartExt(a, b, c, d, 1.0f);
}
