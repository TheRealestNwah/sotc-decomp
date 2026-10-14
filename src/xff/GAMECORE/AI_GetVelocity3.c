float AI_GetVelocity3(float fparg0, float fparg1, float fparg2, float fparg3, float fparg4)
{
    return fparg3 + ((fparg0 / 3.0f) * fparg4 * fparg4 * fparg4) + (fparg1 * 0.5f * fparg4 * fparg4) + (fparg2 * fparg4);
}
