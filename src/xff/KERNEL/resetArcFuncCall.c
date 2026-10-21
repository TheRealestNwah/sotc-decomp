extern int D_000409C4;
extern int D_000409C8;
extern int D_000409CC;
extern int D_000409D0;

void resetArcFuncCall(void)
{
    int *p4 = &D_000409C4;
    int *p8 = &D_000409C8;
    int *pcc = &D_000409CC;
    int *p0 = &D_000409D0;

    *p0 = 0;
    *pcc = 0;
    *p8 = 0;
    *p4 = 0;
}
