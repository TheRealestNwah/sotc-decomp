/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosInitRandom(float seed)
{
    __asm__ __volatile__("mfc1 $6, %0\n"
                         "qmtc2 $6, vf5\n"
                         "vaddw.x vf6, vf5, vf0w\n"
                         "vadd.x vf5, vf5, vf5\n"
                         "vrinit R, vf5x\n"
                         "vrxor R, vf6x\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "f"(seed) : "$6");
}
