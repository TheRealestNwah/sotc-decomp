extern int GAMEUTIL_get_interp_ratio_interp_ratio_cntrl();

int GAMEUTIL_get_cur_interp_ratio_expression(int a, int b, int c, int d)
{
    return GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(a + 20, b, c, d);
}
