typedef int s128 __attribute__((mode(TI)));
union PerceptionVector {
    s128 q;
    float f[4];
    int words[4];
    void *pointers[4];
};

void forceSetPerceptionWork(void *arg0, void *work)
{
    void *context = *(void **)((char *)work + 0x40);

    if (context != 0) {
        void *actor = *(void **)((char *)work + 0x4C);
        float negative;

        ((volatile union PerceptionVector *)work)->q = (*(union PerceptionVector **)((char *)actor + 0x134))->q;
        ((volatile union PerceptionVector *)((char *)work + 0x10))->q = (*(union PerceptionVector **)((char *)actor + 0x134))->q;
        negative = -*(volatile float *)((char *)context + 0x18);
        *(volatile int *)((char *)work + 0x20) = 0;
        *(volatile int *)((char *)work + 0x24) = 0;
        *(volatile float *)((char *)work + 0x28) = negative;
    }
}
