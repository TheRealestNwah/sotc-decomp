extern int GAMEUTIL_init_col_plane_info_filter(int, float, float);

int GAMEUTIL_constructor_col_plane_info_filter(int a)
{
    return GAMEUTIL_init_col_plane_info_filter(a, 0.0f, 0.0f);
}
