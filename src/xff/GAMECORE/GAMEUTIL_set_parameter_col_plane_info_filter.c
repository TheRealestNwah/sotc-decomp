void GAMEUTIL_set_parameter_col_plane_info_filter(char *p, float f1, float f2)
{
    *(float *)(p + 0x70) = f1;
    *(float *)(p + 0x74) = f2;
}
