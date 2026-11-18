typedef struct Hdr {
    unsigned int next : 24;
    unsigned int p0 : 8;
    unsigned int size : 24;
    unsigned int p1 : 8;
    unsigned int x8 : 24;
    unsigned int p2 : 8;
    unsigned int xC : 26;
    unsigned int align : 3;
    unsigned int own : 2;
    unsigned int xC31 : 1;
    unsigned int x10 : 24;
    unsigned int o0 : 8;
    unsigned int x14 : 24;
    unsigned int o1 : 8;
    unsigned int ra : 24;
    unsigned int o2 : 8;
    int x1C;
    int x20;
} Hdr;

extern void *func_00001460(void *, int, int, void *);
extern void func_00002050(void *);
extern void *memcpy(void *, const void *, unsigned int);

static void *func_00002868(void *ptn, void *ptr, int size, int align)
{
    register void *ra __asm__("$31");
    void *t = ra;
    Hdr *h;
    Hdr *nh;
    void *n;
    unsigned int avail;
    unsigned int old;
    int i;
    int own;

    if (align < 4)
        align = 4;
    size = (size + 3) & ~3;
    if (ptr != 0) {
        char *d;
        int m;
        h = ((Hdr **)ptr)[-1];
        d = (char *)(h + 1);
        old = h->size << 2;
        m = align - 1;
        avail = (h->next << 2) - 4;
        avail -= (char *)(((int)d + m) & ~m) - d;
        if (ptn == (void *)(((h->p2 << 16) | (h->p1 << 8) | h->p0) << 2)
            && (1 << (h->align + 2)) >= align && avail >= size) {
            h->size = size >> 2;
            for (i = 0; (align >> (i + 3)) != 0; i++)
                ;
            h->align = i;
            h->ra = (int)t >> 2;
            return ptr;
        }
        n = func_00001460(ptn, size, align, t);
        memcpy(n, ptr, size < old ? size : old);
        nh = ((Hdr **)n)[-1];
        own = (h->o2 << 18) | (h->o1 << 10) | (h->o0 << 2) | h->own;
        nh->own = own;
        nh->o0 = own >> 2;
        nh->o1 = own >> 10;
        nh->o2 = own >> 18;
        func_00002050(ptr);
    } else {
        n = func_00001460(ptn, size, align, ra);
    }
    return n;
}
