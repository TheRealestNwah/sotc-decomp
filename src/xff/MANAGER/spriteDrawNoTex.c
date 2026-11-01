typedef unsigned long u64;
extern void gsReg(int, u64);

void spriteDrawNoTex(int x, int y, int w, int h, int z, int r, int g, int b, int a)
{
    gsReg(0, 0x146);
    gsReg(1, (u64)r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24) | ((u64)0x3F800000 << 32));
    gsReg(4, (u64)((x << 4) + 0x8000) | ((u64)((y << 4) + 0x8000) << 16) | ((u64)z << 32) | ((u64)0xFF00 << 48));
    gsReg(4, (u64)(((x + w) << 4) + 0x8000) | ((u64)(((y + h) << 4) + 0x8000) << 16) | ((u64)z << 32) | ((u64)0xFF00 << 48));
}
