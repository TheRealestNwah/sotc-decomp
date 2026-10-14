extern int GAMEUTIL_get_1p_left_analog_input_extend(int, int, int, float);

int GAMEUTIL_get_1p_left_analog_input(int a, int b)
{
    return GAMEUTIL_get_1p_left_analog_input_extend(a, b, 1, 0.4f);
}
