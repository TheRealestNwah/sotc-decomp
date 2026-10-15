void resetVelocityWormCtrlWork(void *unused, char *w)
{
    *(int *)(w + 0x9C) = 0;
    *(int *)(w + 0x98) = 0;
    *(int *)(w + 0xB4) = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n.set noreorder\n.set reorder\n" : : "r"(w + 0xA0) : "memory");
}
