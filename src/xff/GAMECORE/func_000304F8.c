extern int B_001888D0[2];
extern int D_0017A934;

static void func_000304F8(int id)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (B_001888D0[i] == id) {
            B_001888D0[i] = 0;
        }
    }
    if (D_0017A934 == id) {
        D_0017A934 = 0;
    }
}
