static inline float sqrtF(float x)
{
    float result;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(result) : "f"(x));
    return result;
}

float GAMEUTIL_get_dist_ratio_by_dist_squ(float distanceSquared, float minimum, float maximum)
{
    if (distanceSquared <= minimum * minimum)
        return 0.0f;
    if (maximum * maximum <= distanceSquared)
        return 1.0f;
    return (sqrtF(distanceSquared) - minimum) / (maximum - minimum);
}
