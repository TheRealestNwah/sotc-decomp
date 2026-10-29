extern int checkFadeParam(float *);
extern unsigned char D_00179F18[];

int getDemoBar(void)
{
    return checkFadeParam((float *)D_00179F18);
}
