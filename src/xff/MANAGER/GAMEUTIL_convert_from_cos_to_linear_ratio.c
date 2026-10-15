extern float iosGetACosfExact(float);

float GAMEUTIL_convert_from_cos_to_linear_ratio(float c)
{
    return 1.0f - iosGetACosfExact(c) / 3.1415926f;
}
