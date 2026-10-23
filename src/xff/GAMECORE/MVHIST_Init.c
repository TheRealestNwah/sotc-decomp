typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 a[90];
    s128 b[90];
    int pad[4];
    int c[90];
    int count;
} MvHist;

static inline void zero(s128 *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

void MVHIST_Init(MvHist *h)
{
    s128 *a;
    s128 *b;
    int *c;
    int i;

    c = h->c;
    b = h->b;
    a = h->a;
    for (i = 0; i < 90; i++) {
        zero(a);
        zero(b);
        *c = 0;
        b++;
        a++;
        c++;
    }
    h->count = 0;
}
