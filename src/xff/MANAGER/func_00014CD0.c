#ifdef NONMATCHING
/* 130 diffs, same length (148 words incl. the func_00014EE0 tail). Recovered: text-box bounds calc for a string (tab = 4 half-widths, newline resets x, double-byte advances a full width) then a 4-vertex GS scissor/frame packet via gsReg. The Original tests c < 0x20 with unsigned char c, then (c + 0xE0) & 0xFF < 0x60, re-reading *str for the 9/10 compares; the frame layout (0x50) is smaller than ours (0x60). Permuter not run yet. */
extern int gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int reg, unsigned long value);
extern void iosFTOI4Vector(int *dst, float *src);

static void func_00014CD0(float *pos, unsigned char *str, int *font)
{
    float maxx = pos[0];
    float maxy = pos[1];
    float x = maxx;
    float y = maxy;
    float x0 = maxx;
    int v1;
    unsigned char c;
    float v[4];
    int i4[8];

    v1 = *str;
    while (v1 != 0) {
        c = v1;
        if (c < 0x20) {
            if (*str == 9) {
                x += (float)((((font[4] << 1) - font[6]) >> 1) << 2);
            } else if (*str == 10) {
                x = x0;
                y += (float)(font[5] - font[7]);
            }
        } else if (((v1 + 0xE0) & 0xFF) < 0x60) {
            x += (float)(((font[4] << 1) - font[6]) >> 1);
        } else {
            str++;
            x += (float)((font[4] << 1) - font[6]);
        }
        if (maxx < x)
            maxx = x;
        if (maxy < y)
            maxy = y;
        str++;
        v1 = *str;
    }
    if (str[-1] != 10)
        maxy += (float)(font[5] - font[7]);
    gsRegBegin();
    v[0] = pos[0] + 1.5f;
    v[1] = pos[1] + 1.5f;
    v[2] = maxx + 1.5f;
    v[3] = maxy + 1.5f;
    iosFTOI4Vector(i4, v);
    gsReg(0x42, 0x8000000044UL);
    gsReg(0x4E, 0);
    gsReg(1, 0x3F80000060000000UL);
    gsReg(4, ((unsigned long)((i4[5] + 0x8000) << 16 | (i4[4] + 0x8000))) | 0xFFFFFFFF00000000UL);
    gsReg(4, ((unsigned long)((i4[7] + 0x8000) << 16 | (i4[6] + 0x8000))) | 0xFFFFFFFF00000000UL);
    gsRegEnd();
}
#endif
