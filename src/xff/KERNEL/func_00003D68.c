/* Sync, then wait on the coprocessor-0 condition with the original pipeline spacing. */
static void func_00003D68(void)
{
    __asm__ __volatile__(".set noreorder\n"
                         "sync\n"
                         "1:\n"
                         "nop\n"
                         "nop\n"
                         "nop\n"
                         "nop\n"
                         "nop\n"
                         "bc0f 1b\n"
                         "nop\n"
                         "nop\n"
                         ".set reorder\n");
}
