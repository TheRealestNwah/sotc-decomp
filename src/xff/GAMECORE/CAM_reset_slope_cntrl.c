extern void constructor_double_spring_interp_cntrl(char *, float);
extern void GAMEUTIL_constructor_col_plane_info_filter(char *);
extern void func_000D98F0(char *);

void CAM_reset_slope_cntrl(char *c)
{
    constructor_double_spring_interp_cntrl(c, 0.0001f);
    *(int *)(c + 0x20) = 0;
    *(int *)(c + 0x24) = 0;
    *(int *)(c + 0x28) = 0;
    *(int *)(c + 0x2C) = 0;
    *(int *)(c + 0x30) = 0;
    *(int *)(c + 0x34) = 0;
    *(int *)(c + 0x38) = 0;
    GAMEUTIL_constructor_col_plane_info_filter(c + 0x40);
    GAMEUTIL_constructor_col_plane_info_filter(c + 0xC0);
    func_000D98F0(c);
}
