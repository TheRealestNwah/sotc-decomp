typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void AI_InitAnimalWork(char *pa0, int xa1)
{
    *(int *)(pa0 + 0x0) = xa1;
    *(int *)(pa0 + 0x10) = 0;
    *(int *)(pa0 + 0x4) = -1;
    *(int *)(pa0 + 0xC) = 0;
    *(int *)(pa0 + 0x8) = -1;
}
