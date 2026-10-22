static inline void zeroPoint(void *out)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(out) : "memory");
}
void initGazeIKWork(void *a, void *b, char *work)
{
    zeroPoint(work);
    zeroPoint(work + 0x10);
    zeroPoint(work + 0x20);
    *(int *)(work + 0x30) = 0;
    *(float *)(work + 0x40) = 90.0f;
    *(float *)(work + 0x38) = 1.0f;
    *(float *)(work + 0x3C) = 1.0f;
    *(float *)(work + 0x34) = 1.0f;
    *(int *)(work + 0x60) = 0;
    zeroPoint(work + 0x50);
    *(float *)(work + 0x74) = 1.0f;
    *(int *)(work + 0x64) = 0;
    *(int *)(work + 0x68) = 0;
    *(int *)(work + 0x6C) = 0;
    *(int *)(work + 0x70) = 0;
    zeroPoint(work + 0x80);
    *(int *)(work + 0x90) = 0;
    *(int *)(work + 0x94) = 0;
    *(int *)(work + 0xB0) = 0;
    *(int *)(work + 0x98) = 0;
    zeroPoint(work + 0xA0);
    *(int *)(work + 0xB4) = 0;
    *(int *)(work + 0xB8) = 0;
    *(int *)(work + 0xBC) = 0;
}


