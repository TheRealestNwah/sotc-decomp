typedef int s128 __attribute__((mode(TI)));
struct Quad { s128 q; };
extern struct Quad ZeroPoint;
extern struct Quad B_001885D0;
extern struct Quad B_001885E0;
extern int D_0017A2C4;
extern int D_0017A2C8;

void reloadStage(int a, int b)
{
    struct Quad v[2];

    v[0] = ZeroPoint;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&v[1]) : "memory");
    if (a != 0) {
        D_0017A2C4 = a;
        D_0017A2C8 = b;
        B_001885D0 = v[0];
        B_001885E0 = v[1];
    }
}
