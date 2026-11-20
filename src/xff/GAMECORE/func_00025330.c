/* Draws a text line with the font widths in D_0017A420, aligned by mode (centre, right, left) and faded by the line's position. The screen-centre offset of y is pinned to $v1 so the subtractions get the Original's registers. */
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void gsRegBegin(void);
extern void gsReg(long, long);
extern void gsRegEnd(void);
extern int func_00025188(int, int, int);
extern float D_0017A850;
extern int D_0017A420[];
extern int B_00188620[];
extern int B_00188630[];
extern int B_00188640[];
extern int D_0017A824;
extern int D_0017A840;
extern int D_0017A844;
extern int D_0017A848;

static void func_00025330(int y, unsigned char *str, int mode)
{
    int alpha = (int)(D_0017A850 * 128.0f);
    int x = 0;
    int line = y >> 4;
    int sw = getDrawScreenWidth();
    int sh = getDrawScreenHeight();
    unsigned char *s;
    int width;
    int px;

    switch (mode) {
    case 0:
    case 1:
        {
            unsigned char *p = str;
            width = 0;
            while (*p != 0)
                width += D_0017A420[*p++];
        }
        x = ((B_00188620[0] + B_00188620[1] - width) >> 1) << 4;
        break;
    case 2:
    case 3:
        {
            unsigned char *p = str;
            width = 0;
            while (*p != 0)
                width += D_0017A420[*p++];
        }
        x = (B_00188620[1] - width) << 4;
        break;
    case 4:
    case 5:
        x = B_00188620[0] << 4;
        break;
    }
    if (line < B_00188630[1] && B_00188630[1] != B_00188630[0]) {
        alpha = B_00188640[3] * (line + (D_0017A824 >> 1) - B_00188630[0]) / (B_00188630[1] - B_00188630[0]);
    } else if (B_00188630[2] < line && B_00188630[2] != B_00188630[3]) {
        alpha = B_00188640[3] * (line + (D_0017A824 >> 1) - B_00188630[3]) / (B_00188630[2] - B_00188630[3]);
    }
    alpha = alpha < 0 ? 0 : (alpha > 0x80 ? 0x80 : alpha);
    {
        register int hy __asm__("$3");
        int hx;
        hy = (sh >> 1) << 4;
        hx = (sw >> 1) << 4;
        y -= hy;
        x -= hx;
    }
    gsRegBegin();
    gsReg(1, (long)B_00188640[0] | ((long)B_00188640[1] << 8) | ((long)B_00188640[2] << 16) | ((long)alpha << 24) | 0x3F80000000000000L);
    if (D_0017A848 != 0) {
        int yy;
        px = x + D_0017A840;
        yy = y + D_0017A844;
        s = str;
        gsReg(0x42, 0x8000000042L);
        for (; *s != 0; s++)
            px = func_00025188(px, yy, *s);
    }
    gsReg(0x42, 0x8000000044L);
    px = x;
    for (s = str; *s != 0; s++)
        px = func_00025188(px, y, *s);
    gsRegEnd();
}

