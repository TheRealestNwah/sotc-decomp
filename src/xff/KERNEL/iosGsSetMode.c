typedef struct {
    int width;
    int height;
    int dispW;
    int dispH;
    char pad10[0x90];
    int interlace;
    int pal;
} GsMode;

extern GsMode B_00065550;
extern int D_00040B30;
extern int D_00040B34;
extern int D_00040B38;
void iosGsSetMode(void)
{
    if (B_00065550.pal != 0) {
        B_00065550.interlace = 0;
        B_00065550.dispW = 0x200;
        B_00065550.dispH = 0x1A0;
        B_00065550.width = 0x280;
        B_00065550.height = 0x1C0;
        D_00040B30 = 0;
        D_00040B34 = 0x50;
        D_00040B38 = 1;
    } else {
        B_00065550.interlace = 1;
        B_00065550.dispW = 0x200;
        B_00065550.width = 0x200;
        B_00065550.dispH = 0x1C0;
        B_00065550.height = 0x1C0;
        D_00040B30 = 1;
        D_00040B34 = 2;
        D_00040B38 = 0;
    }
}
