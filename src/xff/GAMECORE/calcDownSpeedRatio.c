float calcDownSpeedRatio(float height, float gravity, float time)
{
    float ratio;

    height -= 0.005f;
    if (height > 0.0f) {
        ratio = height / (-gravity * time);
        if (ratio >= 1.0f) {
            ratio = 1.0f;
        } else {
            ratio *= 0.9f;
        }
    } else {
        ratio = 0.0f;
    }
    return ratio;
}
