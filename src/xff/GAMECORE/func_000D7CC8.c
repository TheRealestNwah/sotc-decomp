typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 ZeroPoint;

static void func_000D7CC8(char *p)
{
    *(int *)(p + 0x4) = 0;
    *(s128 *)(p + 0x20) = ZeroPoint.q;
    *(int *)(p + 0x30) = 0;
    *(int *)(p + 0x34) = 0;
}
