typedef unsigned long u64;
typedef unsigned int u32;

extern void gsReg();

/* Parked draft: draws a flat-shaded sprite rectangle through the GS register list. */
#ifdef NONMATCHING
static void func_000D5CE8(float *rect, u64 z, u32 *col)
{
    u64 zs = z << 32;
    u64 top = 0xFF00UL << 48;
    float fy = rect[1];
    float fx = rect[0];
    int y0 = (int)((fy + 2048.0f) * 16.0f);
    int x0 = (int)((fx + 2048.0f) * 16.0f);
    int x1 = (int)((fx + rect[2] + 2048.0f) * 16.0f);
    int y1 = (int)((fy + rect[3] + 2048.0f) * 16.0f);
    u64 t1 = (u64)col[1] << 8;
    u64 t2 = ((u64)col[2] << 16) | t1;
    u64 c = col[0] | (0xFE00UL << 46) | t2 | ((u64)col[3] << 24);
    u64 a, b, d, e;

    gsReg(1, c, t2, t1, 0);
    a = zs | ((u64)(u32)y0 << 16);
    e = (u64)(u32)x0 | a | top;
    b = zs | ((u64)(u32)y1 << 16);
    gsReg(0, 0x4D);
    gsReg(4, e);
    d = (u64)(u32)x1 | a | top;
    gsReg(4, d);
    gsReg(4, (u64)(u32)x1 | b | top);
    gsReg(4, (u64)(u32)x0 | b | top);
    gsReg(4, e);
    gsReg(0, 0x8A);
    gsReg(1, ((u64)col[3] << 24) | 0x3F80000000A0A0A0UL);
    gsReg(4, e);
    gsReg(4, d);
    gsReg(4, (u64)(u32)x1 | b | top);
    gsReg(4, (u64)(u32)x0 | b | top);
}
#endif
