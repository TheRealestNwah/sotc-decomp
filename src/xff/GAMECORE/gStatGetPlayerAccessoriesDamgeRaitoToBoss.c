#define NULL ((void *)0)
extern void *D_0017A28C;
extern void *D_0017A290;

float gStatGetPlayerAccessoriesDamgeRaitoToBoss(void)
{
    float var_f0;
    float var_f1;

    var_f0 = 1.0f;
    if (D_0017A28C != NULL) {
        var_f0 = (*(float *)((char *)(D_0017A28C) + 0xC));
    }
    var_f1 = var_f0;
    if (D_0017A290 != NULL) {
        var_f1 *= (*(float *)((char *)(D_0017A290) + 0xC));
    }
    return var_f1;
}
