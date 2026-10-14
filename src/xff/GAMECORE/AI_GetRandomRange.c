extern float iosGetRandom();

float AI_GetRandomRange(float fparg0, float fparg1)
{
    return fparg0 + ((fparg1 - fparg0) * iosGetRandom());
}
