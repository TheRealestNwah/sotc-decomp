float AI_GetPosition3(float fparg0, float fparg1, float fparg2, float fparg3, float fparg4, float fparg5)
{
    float temp_f1;
    float temp_f2;

    temp_f2 = fparg5 * fparg5;
    temp_f1 = temp_f2 * fparg5;
    return fparg3 + ((fparg0 * (temp_f1 * fparg5)) / 12.0f) + ((fparg1 * temp_f1) / 6.0f) + (fparg2 * 0.5f * temp_f2) + (fparg4 * fparg5);
}
