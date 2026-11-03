typedef struct {
    char pad0[0x14];
    float weight;
    float fixed;
    union { float f; int i; char c; } u;
    char pad20[0x28 - 0x20];
    unsigned long long flags;
    char pad30[0x58 - 0x30];
} Part;

typedef struct {
    char pad0[0x10];
    Part *parts;
    char pad14[0x40 - 0x14];
    float total;
    char pad44[0x54 - 0x44];
    int n;
    char pad58[0xE8 - 0x58];
    char *work;
} W;

extern void *memset(void *, int, unsigned int);
extern void _gameIWorkSet(int, int);

static void func_0003C778(W *w, int keep)
{
    float sum = 0.0f;
    float fixed = sum;
    float total = w->total;
    float lim = total * 0.39999998f;
    int i;

    if (!keep) {
        memset(w->work + 0x24, 0, w->n << 3);
        _gameIWorkSet(0xE, -1);
    }
    for (i = 0; i < w->n; i++) {
        Part *p = &w->parts[i];

        if (!(p->flags & 0xC0000000000000ULL))
            sum += p->weight;
        else
            fixed += p->fixed;
    }
    if (fixed < total)
        w->total = fixed;
    for (i = 0; i < w->n; i++) {
        Part *p = &w->parts[i];

        if (!(p->flags & 0xC0000000000000ULL)) {
            if (0.0f < sum)
                p->u.f = lim * (p->weight / sum);
            else
                p->u.f = 0.0f;
        } else
            p->u.f = p->fixed;
    }
}
