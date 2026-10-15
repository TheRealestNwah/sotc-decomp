extern int D_00136180;
extern void func_00023010(void);
extern void func_00024878(void);

void solarFlare(void)
{
    int m;
    switch (D_00136180) {
    case 0:
        break;
    case 1:
        func_00023010();
        break;
    case 2:
        func_00024878();
        m = 0;
        break;
    }
}
