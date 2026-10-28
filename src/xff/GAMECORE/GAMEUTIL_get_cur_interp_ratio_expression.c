extern float GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(void *);

float GAMEUTIL_get_cur_interp_ratio_expression(char *object)
{
    return GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(object + 20);
}
