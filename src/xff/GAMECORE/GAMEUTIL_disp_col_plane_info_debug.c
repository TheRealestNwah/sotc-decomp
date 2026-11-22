extern char RO_0017C728[];
extern char RO_0017C738[];
extern char RO_0017C750[];
extern char RO_0017C768[];
extern char RO_0017C778[];
extern char RO_0017C788[];
extern void kColor(int, float, float, float, float);
extern void kPrintf(int x, int y, const char *fmt, ...);

float GAMEUTIL_disp_col_plane_info_debug(char *plane, float x, float y, float dy)
{

    kColor(0, 0.6f, 1.0f, 0.6f, 1.0f);
    if (*(int *)(plane + 8) == 1) {
        kPrintf((int)x, (int)y, RO_0017C728);
        y += dy;
        kPrintf((int)x, (int)y, RO_0017C738, *(float *)(plane + 0x20), *(float *)(plane + 0x24), *(float *)(plane + 0x28));
        y += dy;
        kPrintf((int)x, (int)y, RO_0017C750, *(float *)(plane + 0x30), *(float *)(plane + 0x34), *(float *)(plane + 0x38));
        y += dy;
        if (*(int *)(plane + 0x50) != 0)
            kPrintf((int)x, (int)y, RO_0017C768);
        else
            kPrintf((int)x, (int)y, RO_0017C778);
        y += dy;
    } else {
        kPrintf((int)x, (int)y, RO_0017C788);
        y += dy;
    }
    return y;
}
