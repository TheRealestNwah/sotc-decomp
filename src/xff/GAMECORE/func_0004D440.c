/* VIF packet walker (sibling of func_0004C4D8): skips to each unpack command (top byte with bits 0x60 set) and over its payload, sized from the vn/vl table, storing the first payload's address & 0x7FFF to *out and the payload pointers for the second unpack, the optional count block (+0x1C), the flag-bit-2 block and the descriptor bit-0 block into the record left in v0 (cleared first), skipping the 0x30-flag and trailing blocks, and returns the word past the last payload. The record arrives uninitialised in v0 as in the Original, and the frame copy of it is int-typed to keep the Original's store order. */
typedef struct {
    int a;
    int b;
    int c;
    int d;
    char *e;
} W;

typedef struct {
    char pad[0x18];
    union {
        long flags;
        struct {
            int lo;
            unsigned int n;
        } w;
    } u;
} H;

static const int RO_0017D2E0[] = { 32, 16, 8, 5 };

static inline unsigned int *findUnpack(unsigned int *p, int *size)
{
    unsigned int c;

    while (((*p >> 24) & 0x60) != 0x60)
        p++;
    c = *p;
    *size = ((RO_0017D2E0[(c >> 24) & 3] * ((int)(((c >> 24) & 0xF) >> 2) + 1)) >> 5) * (int)((c >> 16) & 0xFF);
    return p + 1;
}

#define SKIP(p, size) p = findUnpack(p, sz)

static unsigned int *func_0004D440(int *out, unsigned int *p, H *h)
{
    register W *v asm("$2");
    W *w;
    struct {
        int w;
        int size;
    } L;
    int *sz = &L.size;

    L.w = (int)v;
    w = v;
    w->a = 0;
    w->c = 0;
    w->b = 0;
    SKIP(p, L.size);
    *out = *p & 0x7FFF;
    p += L.size;
    SKIP(p, L.size);
    w->d = (int)p;
    p += L.size;
    if (h->u.flags & 0x30) {
        SKIP(p, L.size);
        p += L.size;
    }
    if (h->u.w.n) {
        SKIP(p, L.size);
        w->c = (int)p;
        p += L.size;
    }
    if ((int)(h->u.flags >> 2) & 1) {
        SKIP(p, L.size);
        w->b = (int)p;
        p += L.size;
    }
    if (*(int *)(w->e + 0x18) & 1) {
        SKIP(p, L.size);
        w->a = (int)p;
        p += L.size;
    }
    if (h->u.w.n >= 2 || ((int)(h->u.flags >> 5) & 1)) {
        SKIP(p, L.size);
        p += L.size;
    }
    return p;
}
