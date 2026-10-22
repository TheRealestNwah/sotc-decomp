extern int B_00054800[];
extern int D_000409B0;

void InitQuaternionDrive(void)
{
    D_000409B0 = 0;
    __asm__ __volatile__(".set noreorder\n"
        "sqc2 vf0, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(B_00054800) : "memory");
}
