typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void MakeCollisionEdgePointer(char *pa0, char *pa1, int xa2)
{
    *(int *)(pa0 + 0x0) = *(int *)(pa1 + 0x0);
    *(int *)(pa0 + 0x4) = *(int *)(pa1 + 0x4);
    *(int *)(pa0 + 0x8) = xa2;
}
