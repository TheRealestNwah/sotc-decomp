/* Builds a GS packet that draws one textured sprite between the texture area and the frame buffer, and sends it on PATH3. */
typedef int u_long128 __attribute__((mode(TI)));
typedef unsigned long u_long;

extern void FlushCache(int mode);

typedef struct {
    unsigned long NLOOP : 15;
    unsigned long EOP : 1;
    unsigned long pad16 : 16;
    unsigned long id : 14;
    unsigned long PRE : 1;
    unsigned long PRIM : 11;
    unsigned long FLG : 2;
    unsigned long NREG : 4;
    unsigned long REGS0 : 4;
    unsigned long REGS1 : 4;
    unsigned long REGS2 : 4;
    unsigned long REGS3 : 4;
    unsigned long REGS4 : 4;
    unsigned long REGS5 : 4;
    unsigned long REGS6 : 4;
    unsigned long REGS7 : 4;
    unsigned long REGS8 : 4;
    unsigned long REGS9 : 4;
    unsigned long REGS10 : 4;
    unsigned long REGS11 : 4;
    unsigned long REGS12 : 4;
    unsigned long REGS13 : 4;
    unsigned long REGS14 : 4;
    unsigned long REGS15 : 4;
} sceGifTag;

typedef struct {
    int w;
    int h;
    int tw;
    int th;
} GsSize;

typedef union {
    u_long128 q[16];
    sceGifTag tag;
    u_long ad[32];
} CopyPacket;

extern GsSize B_00065550;
extern CopyPacket B_00065450;

static inline int log2i(int n)
{
    int i;

    for (i = 0; i < 11; i++) {
        if (n <= (1 << i)) {
            return i;
        }
    }
    return -1;
}

static inline void send_path3(long addr, long qwc)
{
    int stat;

    do {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(stat));
    } while ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) ||
             (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) ||
             (*(volatile int *)0x10003020 & 0xC00));
    *(volatile int *)0x1000A020 = qwc;
    *(volatile int *)0x1000A010 = addr & 0x0FFFFFFF;
    FlushCache(0);
    *(volatile int *)0x1000A000 = 0x141;
}

void iosCopyFrameBuffer(void)
{
    int th;
    int tw;

    B_00065450.q[0] = 0;
    B_00065450.tag.NLOOP = 15;
    B_00065450.tag.EOP = 1;
    B_00065450.tag.NREG = 1;
    B_00065450.tag.REGS0 = 0xE;
    B_00065450.ad[2] = (u_long)((B_00065550.w >> 6) & 0x3F) << 16 | (u_long)1 << 24;
    B_00065450.ad[3] = 0x4C; /* FRAME_1 */
    B_00065450.ad[4] = (u_long)(B_00065550.w * B_00065550.h >> 11) | (u_long)0x31 << 24 | (u_long)1 << 32;
    B_00065450.ad[5] = 0x4E; /* ZBUF_1 */
    B_00065450.ad[6] = 0x30000;
    B_00065450.ad[7] = 0x47; /* TEST_1 */
    B_00065450.ad[8] = 0;
    B_00065450.ad[9] = 8; /* CLAMP_1 */
    B_00065450.ad[10] = (u_long)(B_00065550.w - 1) << 16 | (u_long)(B_00065550.h - 1) << 48;
    B_00065450.ad[11] = 0x40; /* SCISSOR_1 */
    B_00065450.ad[12] = (u_long)((0x800 - B_00065550.w / 2) << 4) | (u_long)((0x800 - B_00065550.h / 2) << 4) << 32;
    B_00065450.ad[13] = 0x18; /* XYOFFSET_1 */
    B_00065450.ad[14] = 1;
    B_00065450.ad[15] = 0x3F; /* TEXFLUSH */
    th = log2i(B_00065550.th);
    tw = log2i(B_00065550.tw);
    B_00065450.ad[16] = (u_long)((B_00065550.w * B_00065550.h >> 6) + (B_00065550.tw * B_00065550.th >> 6)) | (u_long)(B_00065550.tw >> 6) << 14 |
             (u_long)1 << 20 | (u_long)tw << 26 | (u_long)th << 30;
    B_00065450.ad[17] = 6; /* TEX0_1 */
    if (B_00065550.w == B_00065550.tw && B_00065550.h == B_00065550.th) {
        B_00065450.ad[18] = 0;
    } else {
        B_00065450.ad[18] = 0x60;
    }
    B_00065450.ad[19] = 0x14; /* TEX1_1 */
    B_00065450.ad[20] = 0x3F80000080808080;
    B_00065450.ad[21] = 1; /* RGBAQ */
    B_00065450.ad[22] = 0x116;
    B_00065450.ad[23] = 0; /* PRIM */
    if (B_00065550.w == B_00065550.tw && B_00065550.h == B_00065550.th) {
        B_00065450.ad[24] = 0;
        B_00065450.ad[25] = 3;
        B_00065450.ad[26] = (u_long)((0x800 - (B_00065550.w >> 1)) << 4) | (u_long)((0x800 - (B_00065550.h >> 1)) << 4) << 16 |
                 (u_long)0xFFFFFFFF << 32;
        B_00065450.ad[27] = 4;
        B_00065450.ad[28] = (u_long)(B_00065550.w << 4) | (u_long)(B_00065550.h << 4) << 16;
        B_00065450.ad[29] = 3;
        B_00065450.ad[30] = (u_long)((0x800 + (B_00065550.w >> 1)) << 4) | (u_long)((0x800 + (B_00065550.h >> 1)) << 4) << 16 |
                 (u_long)0xFFFFFFFF << 32;
        B_00065450.ad[31] = 4;
    } else {
        B_00065450.ad[24] = 0x80008;
        B_00065450.ad[25] = 3;
        B_00065450.ad[26] = (u_long)(((0x800 - (B_00065550.w >> 1)) << 4) - 8) |
                 (u_long)(((0x800 - (B_00065550.h >> 1)) << 4) - 8) << 16 | (u_long)0xFFFFFFFF << 32;
        B_00065450.ad[27] = 4;
        B_00065450.ad[28] = (u_long)((B_00065550.tw << 4) - 0x18) | (u_long)((B_00065550.th << 4) - 0x18) << 16;
        B_00065450.ad[29] = 3;
        B_00065450.ad[30] = (u_long)(((0x800 + (B_00065550.w >> 1)) << 4) - 8) |
                 (u_long)(((0x800 + (B_00065550.h >> 1)) << 4) - 8) << 16 | (u_long)0xFFFFFFFF << 32;
        B_00065450.ad[31] = 4;
    }
    send_path3((unsigned int)&B_00065450, (int)(B_00065450.ad[0] & 0x7FFF) + 1);
}
