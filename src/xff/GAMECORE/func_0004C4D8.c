/* VIF packet walker for a model chunk: skips to each UNPACK command (the 0x60 bits of the top byte), sizes its payload from RO_0017D230 (bits per element for vl) * (vn + 1) / 32 * num, and steps over it. It records the first payload's index (& 0x7FFF) in *out and the second payload in w->c, skips the optional blocks selected by the flags at h+0x18 and the count at h+0x1C, and stores the blocks for flag bit 2 and for w->d+0x18 bit 0 in w->a and w->b. w is never initialised in the Original: it is whatever the caller left in $v0, read through a pinned register and stored to the frame. The frame copy is int-typed so the scheduler keeps it ahead of the w->a/w->b stores, as in the Original. */
typedef struct {
    int a;
    int b;
    int c;
    char *d;
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

static const int RO_0017D230[] = { 32, 16, 8, 5 };

static inline unsigned int *findUnpack(unsigned int *p, int *size)
{
    unsigned int c;

    while (((*p >> 24) & 0x60) != 0x60)
        p++;
    c = *p;
    *size = ((RO_0017D230[(c >> 24) & 3] * ((int)(((c >> 24) & 0xF) >> 2) + 1)) >> 5) * (int)((c >> 16) & 0xFF);
    return p + 1;
}

static unsigned int *func_0004C4D8(int *out, unsigned int *p, H *h)
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
    w->b = 0;
    p = findUnpack(p, sz);
    *out = *p & 0x7FFF;
    p += L.size;
    p = findUnpack(p, sz);
    w->c = (int)p;
    p += L.size;
    if (h->u.flags & 0x30) {
        p = findUnpack(p, sz);
        p += L.size;
    }
    if (h->u.w.n) {
        p = findUnpack(p, sz);
        p += L.size;
    }
    if ((int)(h->u.flags >> 2) & 1) {
        p = findUnpack(p, sz);
        w->a = (int)p;
        p += L.size;
    }
    if (*(int *)(w->d + 0x18) & 1) {
        p = findUnpack(p, sz);
        w->b = (int)p;
        p += L.size;
    }
    if (h->u.w.n >= 2 || ((int)(h->u.flags >> 5) & 1)) {
        p = findUnpack(p, sz);
        p += L.size;
    }
    return p;
}
