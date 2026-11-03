extern int D_00139BF8;
extern int D_00139BFC;
extern int D_00139C00;

static void func_000DCCA8(int a, int b, int c, int *out)
{
    int v;

    switch (D_00139BF8) {
    case 0:
        *out = -2;
        return;
    case 1:
        break;
    default:
        v = D_00139C00;
        D_00139C00 = 0;
        if (v) {
            *out = D_00139BFC;
            return;
        }
        break;
    }
    *out = -1;
}
