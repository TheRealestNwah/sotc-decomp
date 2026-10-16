void GAMEUTIL_reset_interp_ratio_cntrl(int *p)
{
    p[2] = 1;
    p[3] = 0;
    if (p[0] == 1)
        *(float *)&p[4] = 0.0f;
    else
        *(float *)&p[4] = 1.0f;
}
