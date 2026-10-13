extern void fruitsFlagSet(int, int);
extern int D_0017A028;
extern int D_0017A02C;

void resetTreeId(int arg0)
{
    int var_a1;
    int var_s0;

    var_s0 = D_0017A02C;
    if (var_s0 < 0x20) {
        var_a1 = var_s0;
        do {
            var_s0 += 1;
            fruitsFlagSet(arg0, var_a1);
            var_a1 = var_s0;
        } while (var_s0 < 0x20);
    }
    D_0017A02C = 0;
    D_0017A028 = arg0;
}
