extern void GAMEUTIL_init_col_plane_info_filter(char *, float, float);

void GAMEUTIL_constructor_col_plane_info_filter(char *filter)
{
    GAMEUTIL_init_col_plane_info_filter(filter, 0.0f, 0.0f);
}
