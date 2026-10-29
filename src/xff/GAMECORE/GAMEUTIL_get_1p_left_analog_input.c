extern void GAMEUTIL_get_1p_left_analog_input_extend(float *, float *, int, float);

void GAMEUTIL_get_1p_left_analog_input(float *x, float *z)
{
    GAMEUTIL_get_1p_left_analog_input_extend(x, z, 1, 0.4f);
}
