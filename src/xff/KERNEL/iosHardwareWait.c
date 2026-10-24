/* Coprocessor-condition waits retain the original pipeline spacing. */
int iosWaitDMA(void)
{
    __asm__ __volatile__(".set noreorder\n"
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
    return 0;
}

int iosWaitVU1(void)
{
    __asm__ __volatile__(".set noreorder\n"
                         "1:\n"
                         "nop\n"
                         "nop\n"
                         "nop\n"
                         "nop\n"
                         "nop\n"
                         "bc2t 1b\n"
                         "nop\n"
                         "nop\n"
                         ".set reorder\n");
    return 0;
}
