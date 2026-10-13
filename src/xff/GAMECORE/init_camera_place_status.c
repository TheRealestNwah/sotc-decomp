extern void GAMEUTIL_constructor_col_plane_info_filter(void *);
extern void func_000D98D8();

void init_camera_place_status(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x10)) = -1;
    (*(int *)((char *)(arg0) + 0)) = 0;
    (*(int *)((char *)(arg0) + 4)) = 0;
    (*(int *)((char *)(arg0) + 8)) = 0;
    (*(int *)((char *)(arg0) + 0xC)) = 0;
    (*(int *)((char *)(arg0) + 0x14)) = 0;
    func_000D98D8();
    GAMEUTIL_constructor_col_plane_info_filter(arg0 + 0xD0);
    GAMEUTIL_constructor_col_plane_info_filter(arg0 + 0x150);
}
