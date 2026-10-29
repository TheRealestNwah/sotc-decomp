extern int checkFadeParam(float *);
extern unsigned char D_00179F00[];

int getFade(void)
{
    return checkFadeParam((float *)D_00179F00);
}
