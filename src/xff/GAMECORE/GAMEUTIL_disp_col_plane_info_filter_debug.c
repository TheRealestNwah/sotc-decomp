extern char RO_0017C798[];
extern char RO_0017C7B8[];
extern float GAMEUTIL_disp_col_plane_info_debug(void *plane, float x, float y, float dy);
extern void kPrintf(int x, int y, const char *fmt, ...);

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

float GAMEUTIL_disp_col_plane_info_filter_debug(char *plane, float x, float y0, float dy)
{
    float y = GAMEUTIL_disp_col_plane_info_debug(plane, x, y0, dy);
    kPrintf((int)x, (int)y, RO_0017C798, *(float *)(plane + 0x6C), *(float *)(plane + 0x74));
    y += dy;
    kPrintf((int)x, (int)y, RO_0017C7B8, fsqrt(*(float *)(plane + 0x64)), *(float *)(plane + 0x70));
    y += dy;
    return y + dy;
}
