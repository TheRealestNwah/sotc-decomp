extern float powf(float, float);

float GAMEUTIL_get_interp_value_ratio_pow(float a, float b, float t, float power)
{
    float ratio = powf(t, power);
    float result;

    if (ratio <= 0.0f) {
        result = b;
        goto done;
    }
    if (ratio >= 1.0f) {
        result = a;
        goto done;
    }
    if (a == b) {
        result = a;
        goto done;
    }
    result = (ratio * a) + ((1.0f - ratio) * b);

done:
    return result;
}
