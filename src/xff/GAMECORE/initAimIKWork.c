typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 a;
    s128 b;
    int c;
    int d;
    float e;
} AimIKWork;

void initAimIKWork(void *x, void *y, AimIKWork *w)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&w->a) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&w->b) : "memory");
    w->c = 0;
    w->d = 0;
    w->e = 1.0f;
}
