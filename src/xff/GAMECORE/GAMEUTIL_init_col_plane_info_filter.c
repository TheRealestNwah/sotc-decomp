typedef int s128 __attribute__((mode(TI)));
extern s128 YUnitVector, ZeroPoint;
extern void GAMEUTIL_set_parameter_col_plane_info_filter(char *);

void GAMEUTIL_init_col_plane_info_filter(char *f)
{
    *(int *)(f + 0) = 0;
    *(int *)(f + 4) = 0;
    *(int *)(f + 8) = 0;
    *(long *)(f + 0x10) = 0;
    *(s128 *)(f + 0x20) = YUnitVector;
    *(s128 *)(f + 0x30) = ZeroPoint;
    *(s128 *)(f + 0x40) = ZeroPoint;
    *(int *)(f + 0x50) = 0;
    *(int *)(f + 0x60) = 0;
    *(int *)(f + 0x64) = 0;
    *(int *)(f + 0x68) = 0;
    *(int *)(f + 0x6C) = 0;
    GAMEUTIL_set_parameter_col_plane_info_filter(f);
}
