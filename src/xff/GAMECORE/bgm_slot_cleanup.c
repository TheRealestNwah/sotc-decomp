/* Completion callbacks for the active BGM slots. */
extern void *D_0017A970;
extern void *B_001888D8[2];
extern void *D_0017A934;

static void func_00030558(void *slot)
{
    if (slot == D_0017A970) {
        D_0017A970 = 0;
    }
}

static void func_00030578(void *slot)
{
    int i;

    for (i = 0; i < 2; i++) {
        if (B_001888D8[i] == slot) {
            B_001888D8[i] = 0;
        }
    }
    if (D_0017A934 == slot) {
        D_0017A934 = 0;
    }
}
