extern void gsReg(long, long);
extern int D_0017A82C, D_0017A830, D_0017A420[];

#ifdef NONMATCHING /* 109 diffs, same word count: GS register packing, temporaries hoisted differently */
static void func_00025188(int base, int dst, unsigned int id0)
{
    unsigned int id = id0 & 0xFF;
    int x = id & 0xF;
    int y = id >> 4;
    int w = D_0017A82C;
    int h = D_0017A830;
    int xw = x * w;
    int yh = y * h;
    int s4 = D_0017A420[id];
    int ya = yh + h;
    int t = base + ((s4 + 0x800) << 4);

    if (((id + 0xDF) & 0xFF) < 0x5A) {
        gsReg(8, ((long)(xw + s4) << 14) | 0xA | ((long)xw << 4) | ((long)ya << 34) | ((long)yh << 24));
        gsReg(3, (long)((xw << 4) + 8) | ((long)((yh << 4) + 8) << 16));
        gsReg(4, (long)(base + 0x8000) | ((long)(dst + 0x8000) << 16) | 0xFFFE524F00000000L);
        gsReg(3, (long)((ya << 4) + 8) << 16 | (long)(((xw + s4) << 4) + 8));
        gsReg(4, (long)(unsigned int)t | ((long)(dst + ((h + 0x800) << 4)) << 16) | 0xFFFE524F00000000L);
    }
}
#endif
