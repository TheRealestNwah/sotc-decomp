#define REG(a) (*(volatile int *)(a))

extern void func_00003D68(void);

static void func_00000FF8(int dst, int src, unsigned int size)
{
    size = size >> 4;
    while (size > 0x400) {
        REG(0x1000E020) = -0x400;
        REG(0x1000E010) = 0x200;
        size -= 0x400;
        REG(0x1000D410) = src;
        src += 0x4000;
        REG(0x1000D420) = 0x400;
        REG(0x1000D480) = 0x70000000;
        REG(0x1000E020) |= 0x200;
        REG(0x1000D400) = 0x101;
        func_00003D68();
        REG(0x1000E020) = -0x400;
        REG(0x1000E010) = 0x100;
        REG(0x1000D010) = dst;
        dst += 0x4000;
        REG(0x1000D020) = 0x400;
        REG(0x1000D080) = 0x70000000;
        REG(0x1000E020) |= 0x100;
        REG(0x1000D000) = 0x100;
        func_00003D68();
    }
    REG(0x1000E020) = -0x400;
    REG(0x1000E010) = 0x200;
    REG(0x1000D410) = src;
    REG(0x1000D420) = size;
    REG(0x1000D480) = 0x70000000;
    REG(0x1000E020) |= 0x200;
    REG(0x1000D400) = 0x101;
    func_00003D68();
    REG(0x1000E020) = -0x400;
    REG(0x1000E010) = 0x100;
    REG(0x1000D010) = dst;
    REG(0x1000D020) = size;
    REG(0x1000D080) = 0x70000000;
    REG(0x1000E020) |= 0x100;
    REG(0x1000D000) = 0x100;
    func_00003D68();
    size = 0;
}
