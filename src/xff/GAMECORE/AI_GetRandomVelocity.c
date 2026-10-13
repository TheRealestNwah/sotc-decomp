extern float iosGetRandom();

void AI_GetRandomVelocity(float *arg0, float *arg1, float *arg2, float fparg0, float fparg1, float fparg2, float fparg3)
{
    if (*arg1 <= *arg2) {
        *arg0 = (fparg0 + ((fparg1 - fparg0) * iosGetRandom())) * fparg2;
        *arg1 = fparg3;
        *arg2 = 0.0f;
    }
}
