typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 pos;
    int a;
    int b;
    int c;
} KitePathPoint;

void Kite_InitKitePathPoint(KitePathPoint *p)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(p) : "memory");
    p->a = -1;
    p->b = 0;
    p->c = -1;
}
