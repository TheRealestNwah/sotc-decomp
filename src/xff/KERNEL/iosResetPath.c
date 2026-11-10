typedef int s128 __attribute__((mode(TI)));
extern s128 D_00040B50[2];

void iosResetPath(void)
{
    /* The register pins reproduce the original's separate loads of the constant 1. */
    register int v __asm__("$3") = 0;

    {
        register int one0 __asm__("$4") = 1;
        *(volatile int *)0x10003C10 = one0;
    }
    __asm__ __volatile__(
        "cfc2.ni %0, $vi28\n"
        "\tori %0, %0, 0x200\n"
        "\tctc2.ni %0, $vi28\n"
        "\tsync.p"
        : "+r"(v));
    *(volatile s128 *)0x10005000 = D_00040B50[0];
    *(volatile s128 *)0x10005000 = D_00040B50[1];
    *(volatile int *)0x10003000 = 1;
}
