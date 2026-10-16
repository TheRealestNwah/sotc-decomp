extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);

float convert_from_slide_bar_value_to_ratio(int v, float lo, float hi)
{
    if (v == 8)
        return 1.0f;
    if (v < 8)
        return GAMEUTIL_get_interp_value(1.0f, lo, GAMEUTIL_get_dist_ratio(v, 0.0f, 8.0f));
    return GAMEUTIL_get_interp_value(hi, 1.0f, GAMEUTIL_get_dist_ratio(v, 8.0f, 15.0f));
}
