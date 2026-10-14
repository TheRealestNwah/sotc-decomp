void CAM_set_param_view_cut_avoid_cntrl(char *p, float f1, float f2)
{
    *(float *)(p + 0x94) = f1;
    *(float *)(p + 0x98) = f2;
}
