typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void AI_InitAnimalOptimize(char *pa0)
{
    *(int *)(pa0 + 0x0) = 1;
    *(float *)(pa0 + 0x4) = 3e+01f;
    *(int *)(pa0 + 0x8) = 0;
}
