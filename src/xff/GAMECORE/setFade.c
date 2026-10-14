extern char D_00179F00[];
extern int setFadeParam();

int setFade(int a, int b, int c, int d)
{
    return setFadeParam((int)D_00179F00, 27, c, d);
}
