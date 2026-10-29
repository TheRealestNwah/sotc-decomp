extern void setBossIndexTimeAttackBestTime(int, float);
extern int B_001887C0;
extern float D_0017A928;

void time_attack_set_best_time(float fparg0)
{
    D_0017A928 = fparg0;
    setBossIndexTimeAttackBestTime(B_001887C0, fparg0);
}
