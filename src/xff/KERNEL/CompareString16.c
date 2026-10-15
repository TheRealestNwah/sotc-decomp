typedef int s128 __attribute__((mode(TI)));

/* Nonzero when the two 16-byte strings differ. */
int CompareString16(s128 *a, s128 *b)
{
    long t[2] __attribute__((aligned(16)));

    __asm__ __volatile__("lq $8, 0x0(%1)\n"
                         "lq $9, 0x0(%2)\n"
                         "pxor $10, $8, $9\n"
                         "sq $10, 0x0(%0)\n"
                         : : "r"(t), "r"(a), "r"(b) : "$8", "$9", "$10", "memory");
    return t[0] | t[1];
}
