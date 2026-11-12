/* Allocates a 0x60-byte path1 packet for a debug line attribute: GIF tag words, then a GS RGBAQ word (r, g, b scaled by 255 and a by 128, with Q = 1.0f in the high word, written with the SCE_GS_SET_RGBAQ field order), a 1, the line width ((width+1) << 17 | 0x11001, or 0x11000 when flag is set), and a prim register selected by mode (2 -> 0x48, 3 -> 0x42, else 0x44). */
typedef unsigned long u64;
extern char *iosAllocPacketPtrPath1(int);

void *debugLineObjectCreateAttributre(int mode, int width, int flag, float r, float g, float b, float a)
{
    char *p = iosAllocPacketPtrPath1(0x60);
    u64 col;
    u64 reg;

    *(u64 *)(p + 0) = 0x60000005UL;
    *(int *)(p + 8) = 0x10000000;
    *(int *)(p + 0x10) = 0x1000101;
    *(int *)(p + 0x14) = 0x3000000;
    *(int *)(p + 0x18) = 0x20001C0;
    *(int *)(p + 0x1C) = 0x50000004;
    *(u64 *)(p + 0x20) = 0x1000000000008003UL;
    *(u64 *)(p + 0x28) = 0xE;
    *(int *)(p + 0xC) = 0;
    col = (u64)(unsigned int)(r * 255.0f) | ((u64)(unsigned int)(g * 255.0f) << 8) | ((u64)(unsigned int)(b * 255.0f) << 16) | ((u64)(unsigned int)(a * 128.0f) << 24) | ((u64)0x3F800000 << 32);
    *(u64 *)(p + 0x30) = col;
    *(u64 *)(p + 0x38) = 1;
    *(u64 *)(p + 0x40) = ((u64)(width + 1) << 17) | (flag == 0 ? 0x11001 : 0x11000);
    *(u64 *)(p + 0x48) = 0x47;
    reg = mode == 2 ? 0x8000000048UL : mode == 3 ? 0x8000000042UL : 0x8000000044UL;
    *(u64 *)(p + 0x50) = reg;
    *(u64 *)(p + 0x58) = 0x42;
    return p;
}
