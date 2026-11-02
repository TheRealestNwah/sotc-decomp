typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;

#define I(o) (*(int *)((char *)p + (o)))
#define F(o) (*(float *)((char *)p + (o)))
#define Q(o) (*(s128 *)((char *)p + (o)))

static void func_000D98F0(void *p)
{
    I(0x140) = 0;
    I(0x144) = 0;
    F(0x148) = 3.4028235e38f;
    I(0x14C) = 0;
    I(0x150) = 0;
    Q(0x160) = ZeroPoint;
    I(0x170) = 0;
    I(0x174) = 0;
    Q(0x180) = ZeroPoint;
    Q(0x190) = ZeroPoint;
    Q(0x1A0) = ZeroPoint;
    Q(0x1B0) = ZeroPoint;
    I(0x1C0) = 0;
    Q(0x1D0) = ZeroPoint;
    I(0x1E0) = 0;
    I(0x1E4) = 0;
    I(0x1E8) = 0;
    F(0x1EC) = 1.0f;
    I(0x1F0) = 0;
    F(0x1F8) = 1.0f;
    F(0x1F4) = 1.0f;
    I(0x1FC) = 5;
    Q(0x200) = ZeroPoint;
    Q(0x210) = ZeroPoint;
    I(0x220) = 0;
    Q(0x230) = ZeroPoint;
    Q(0x240) = ZeroPoint;
    Q(0x250) = ZeroPoint;
    I(0x260) = 0;
    Q(0x270) = ZeroPoint;
}
