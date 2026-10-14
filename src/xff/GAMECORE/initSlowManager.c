extern void isysInitGroup(void *);
extern unsigned char B_00188610[1];
extern int D_0017A418;

void initSlowManager(void)
{
    if (D_0017A418 == 0) {
        isysInitGroup(&B_00188610);
        D_0017A418 = 1;
    }
}
