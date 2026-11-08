#ifdef NONMATCHING
/* Parked: 31 words differ (the Original keeps the result in $v0 and the match flag in $v1; gcc chooses $a3/$t0 and folds p+0x10 != 0). */
int is_base_default_dir_attr_change_game_camera_param_manager(int *p)
{
    int ret = 0;

    if (*p != 0) {
        char *a2 = (char *)p + 0x5C;
        int same;

        int *q = p + 4;

        if (q != 0) {
            char *a0 = (char *)p + 0x6B0;
            int kind = *(int *)(a0 + 0x8C);

            same = 0;
            if (kind == *(int *)(a2 + 0x8C)) {
                same = 0;
                if (*(int *)(a0 + 0xA8) == *(int *)(a2 + 0xA8)) {
                    same = 1;
                    if (kind != 1) {
                        int v = *(int *)(a0 + 0x90);

                        if (v == *(int *)(a2 + 0x90) && (unsigned int)(v - 0x64) < 3) {
                            if (kind != 0 && kind != 4 && kind != 5 && kind != 6)
                                same = 0;
                        } else
                            same = 0;
                    }
                }
            }
        } else
            same = 0;
        ret = 1;
        if (same != 0)
            ret = 0;
    }
    return ret;
}
#else
int is_base_default_dir_attr_change_game_camera_param_manager(int *p);
#endif
