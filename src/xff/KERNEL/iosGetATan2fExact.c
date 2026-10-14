extern float atan2f(float, float);

float iosGetATan2fExact(float y, float x)
{
    if (y > 1.0f) {
        y = 1.0f;
    } else if (y < -1.0f) {
        y = -1.0f;
    }
    if (x > 1.0f) {
        x = 1.0f;
    } else if (x < -1.0f) {
        x = -1.0f;
    }
    return atan2f(y, x);
}
