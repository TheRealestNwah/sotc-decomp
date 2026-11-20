extern int D_00179EA8;
extern unsigned long D_00179EB0;
extern int D_00179EB8;

static void func_0000B688(void)
{
    if (D_00179EA8 != 2) {
        D_00179EB0 += 4999999.5f;
    } else {
        if (D_00179EB8 != 0)
            D_00179EB0 += 4999999.5f;
        else
            D_00179EB0 += 14999999.0f;
        D_00179EB8 = !D_00179EB8;
    }
}
