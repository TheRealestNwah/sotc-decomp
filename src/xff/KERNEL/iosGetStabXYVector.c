void iosGetStabXYVector(int *a0, int *a1)
{
    typedef int qword __attribute__((mode(TI)));
    *(volatile qword *)a0 = *(qword *)a1;
    ((volatile int *)a0)[2] = 0;
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%0)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}
