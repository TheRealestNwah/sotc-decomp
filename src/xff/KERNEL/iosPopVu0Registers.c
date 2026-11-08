typedef int s128 __attribute__((mode(TI)));
extern s128 B_000543F0[];
extern s128 B_000545F0[];
extern void iosDI(void);
extern void iosEI(void);

void iosPopVu0Registers(void)
{
    register s128 *p __asm__("$3");
    register s128 *q __asm__("$2");

    iosDI();
    p = B_000545F0;
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%0)
"
        "	lqc2 $vf6, 0x10(%0)
"
        "	lqc2 $vf7, 0x20(%0)
"
        "	lqc2 $vf1, 0x30(%0)
"
        "	lqc2 $vf2, 0x40(%0)
"
        "	lqc2 $vf3, 0x50(%0)
"
        "	lqc2 $vf4, 0x60(%0)
"
        "	lqc2 $vf8, 0x70(%0)
"
        "	lqc2 $vf9, 0x80(%0)
"
        "	lqc2 $vf10, 0x90(%0)
"
        "	lqc2 $vf11, 0xA0(%0)
"
        "	lqc2 $vf12, 0xB0(%0)
"
        "	lqc2 $vf13, 0xC0(%0)
"
        "	lqc2 $vf14, 0xD0(%0)
"
        "	lqc2 $vf15, 0xE0(%0)
"
        "	lqc2 $vf16, 0xF0(%0)
"
        "	lqc2 $vf17, 0x100(%0)
"
        "	lqc2 $vf18, 0x110(%0)
"
        "	lqc2 $vf19, 0x120(%0)
"
        "	lqc2 $vf20, 0x130(%0)
"
        "	lqc2 $vf21, 0x140(%0)
"
        "	lqc2 $vf22, 0x150(%0)
"
        "	lqc2 $vf23, 0x160(%0)
"
        "	lqc2 $vf24, 0x170(%0)
"
        "	lqc2 $vf25, 0x180(%0)
"
        "	lqc2 $vf26, 0x190(%0)
"
        "	lqc2 $vf27, 0x1A0(%0)
"
        "	lqc2 $vf28, 0x1B0(%0)
"
        "	lqc2 $vf29, 0x1C0(%0)
"
        "	lqc2 $vf30, 0x1D0(%0)
"
        "	lqc2 $vf31, 0x1E0(%0)"
        : : "r"(p) : "memory");
    __asm__ __volatile__(
        "lqc2 $vf1, 0x0(%0)
"
        "	lqc2 $vf2, 0x10(%0)
"
        "	lqc2 $vf3, 0x20(%0)
"
        "	lqc2 $vf4, 0x30(%0)
"
        "	lqc2 $vf5, 0x40(%0)
"
        "	lqc2 $vf6, 0x50(%0)
"
        "	lqc2 $vf7, 0x60(%0)
"
        "	lqc2 $vf8, 0x70(%0)
"
        "	lqc2 $vf9, 0x80(%0)
"
        "	lqc2 $vf10, 0x90(%0)
"
        "	lqc2 $vf11, 0xA0(%0)
"
        "	lqc2 $vf12, 0xB0(%0)
"
        "	lqc2 $vf13, 0xC0(%0)
"
        "	lqc2 $vf14, 0xD0(%0)
"
        "	lqc2 $vf15, 0xE0(%0)
"
        "	lqc2 $vf16, 0xF0(%0)
"
        "	lqc2 $vf17, 0x100(%0)
"
        "	lqc2 $vf18, 0x110(%0)
"
        "	lqc2 $vf19, 0x120(%0)
"
        "	lqc2 $vf20, 0x130(%0)
"
        "	lqc2 $vf21, 0x140(%0)
"
        "	lqc2 $vf22, 0x150(%0)
"
        "	lqc2 $vf23, 0x160(%0)
"
        "	lqc2 $vf24, 0x170(%0)
"
        "	lqc2 $vf25, 0x180(%0)
"
        "	lqc2 $vf26, 0x190(%0)
"
        "	lqc2 $vf27, 0x1A0(%0)
"
        "	lqc2 $vf28, 0x1B0(%0)
"
        "	lqc2 $vf29, 0x1C0(%0)
"
        "	lqc2 $vf30, 0x1D0(%0)
"
        "	lqc2 $vf31, 0x1E0(%0)"
        : : "r"(q = B_000543F0) : "memory");
    iosEI();
}
