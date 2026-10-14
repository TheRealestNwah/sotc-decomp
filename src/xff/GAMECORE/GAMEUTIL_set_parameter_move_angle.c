void GAMEUTIL_set_parameter_move_angle(float *p, float a, float b, float c, float d, float e, float f)
{
    float k = 0.0174532925f;
    p[1] = a * k;
    p[2] = b * k;
    p[3] = c * k;
    p[4] = d;
    p[5] = e * k;
    p[6] = f * k;
}
