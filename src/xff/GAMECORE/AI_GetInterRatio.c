float AI_GetInterRatio(float x, float start, float end, float low, float high)
{
    end -= start;
    if (end == 0.0f) return low;
    return ((x - start) * (high - low)) / end + low;
}
