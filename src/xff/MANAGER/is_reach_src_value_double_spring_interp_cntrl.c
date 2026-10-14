extern float GAMEUTIL_get_difference_value(int, float, float);
extern void GAMEUTIL_is_nearly_equal_zero(float, float);

void is_reach_src_value_double_spring_interp_cntrl(void *arg0, float fparg0)
{
    GAMEUTIL_is_nearly_equal_zero(GAMEUTIL_get_difference_value((*(int *)((char *)(arg0) + 0x14)), (*(float *)((char *)(arg0) + 0x1C)), fparg0), (*(float *)((char *)(arg0) + 0x10)) * 3.0f);
}
