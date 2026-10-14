typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void ResetCharacterClassWaterStatus(char *pa0)
{
    *(char *)(pa0 + 0x361) = 0;
    *(char *)(pa0 + 0x362) = 0;
    *(int *)(pa0 + 0x10C8) = 0;
    *(int *)(pa0 + 0x10C4) = 0;
    *(int *)(pa0 + 0x10CC) = 0;
}
