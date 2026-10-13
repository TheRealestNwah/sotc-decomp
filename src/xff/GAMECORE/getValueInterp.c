extern float getRatioFromInterp(float, float);

float getValueInterp(float fparg0, float fparg1, float fparg2, float fparg3)
{
    float temp_f0;

    temp_f0 = getRatioFromInterp(fparg2, fparg3);
    return (fparg1 * temp_f0) + (fparg0 * (1.0f - temp_f0));
}
