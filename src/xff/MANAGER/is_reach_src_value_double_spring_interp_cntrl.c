extern float GAMEUTIL_get_difference_value(int, float, float);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
int is_reach_src_value_double_spring_interp_cntrl(void *control, float target)
{
    return GAMEUTIL_is_nearly_equal_zero(
        GAMEUTIL_get_difference_value(*(int *)((char *)control + 0x14),
                                      *(float *)((char *)control + 0x1C), target),
        *(float *)((char *)control + 0x10) * 3.0f);
}
