float AI_GetVelocity2(float fparg0, float fparg1, float fparg2, float fparg3)
{
    return fparg2 + (fparg0 * 0.5f * fparg3 * fparg3) + (fparg1 * fparg3);
}
