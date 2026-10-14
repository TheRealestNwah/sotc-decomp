extern int ZeroPoint[];
extern void GAMEUTIL_reset_position_filter(int, int *);
extern int GAMEUTIL_set_parameter_position_filter(int, float);

int GAMEUTIL_constructor_position_filter(int a)
{
    GAMEUTIL_reset_position_filter(a, ZeroPoint);
    return GAMEUTIL_set_parameter_position_filter(a, 0.0f);
}
