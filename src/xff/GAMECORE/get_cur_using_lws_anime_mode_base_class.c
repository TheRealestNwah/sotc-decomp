char *get_cur_using_lws_anime_mode_base_class(char *cam)
{
    int mode = *(int *)(cam + 0x1360);

    if (mode == 7)
        return cam + 0x3270;
    if (mode == 8)
        return cam + 0x34E0;
    return 0;
}
