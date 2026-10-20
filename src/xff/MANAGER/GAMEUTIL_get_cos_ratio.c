extern float powf(float, float);
float GAMEUTIL_get_cos_ratio(float power, float value, float low, float high)
{
    float ratio;
    if (value <= low) {
        ratio = 0.0f;
    }
    else if (high <= value) {
        ratio = 1.0f;
    }
    else {
        ratio = (value - low) / (high - low);
    }
    if (power != 1.0f && 0.0f < ratio && ratio < 1.0f) {
        if (ratio <= 0.5f) {
            ratio = powf(ratio + ratio, power) * 0.5f;
        } else {
            float offset = ratio - 0.5f;
            ratio = (1.0f - powf(1.0f - (offset + offset), power)) * 0.5f + 0.5f;
        }
    }
    return ratio;
}

