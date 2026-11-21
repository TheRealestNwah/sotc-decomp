#ifdef NONMATCHING
/* Parked attempt: 17 diffs (h 0xC word register a1 vs a2, q/r copy store order). */
typedef struct Hdr {
    unsigned int size : 24;
    unsigned int p0 : 8;
    unsigned int off : 24;
    unsigned int p1 : 8;
    unsigned int next : 24;
    unsigned int p2 : 8;
    unsigned int prev : 24;
    unsigned int used : 1;
    unsigned int b25 : 1;
    unsigned int cls : 3;
    unsigned int q : 2;
    unsigned int b31 : 1;
    unsigned int f10 : 24;
    unsigned int r0 : 8;
    unsigned int f14 : 24;
    unsigned int r1 : 8;
    unsigned int f18 : 24;
    unsigned int r2 : 8;
    int pad1c;
} Hdr;

extern unsigned char rootPtn[];
extern int D_00040640[];
extern void func_00002050(void *);

void *func_000024E0(char *ptr, char *p, int n)
{
    Hdr *h = ((Hdr **)ptr)[-1];
    int keep;
    void *ret;
    int off;
    unsigned int size;
    Hdr *b;
    char *data;
    unsigned int next;
    int newsz;
    unsigned int ptn;
    int x;
    int i;

    keep = n;
    if (n < 4) {
        n = 4;
    }
    off = h->off << 2;
    size = h->size;
    if (keep == 0) {
        b = (Hdr *)p;
        p += 0x24;
    } else {
        b = (Hdr *)(p - 0x24);
    }
    data = (char *)h + 0x20;
    if ((char *)b < (char *)h + 0x24) {
        return 0;
    }
    if (p >= data + (h->size << 2)) {
        return 0;
    }
    next = h->next;
    b->prev = (int)h >> 2;
    h->next = (int)b >> 2;
    b->next = next;
    if (next != 0) {
        ((Hdr *)(next << 2))->prev = (int)b >> 2;
    }
    newsz = ((char *)b - (char *)(h + 1)) >> 2;
    ptn = (unsigned)h->p2 << 16 | h->p1 << 8 | h->p0;
    b->p0 = ptn;
    b->p1 = ptn >> 8;
    b->p2 = ptn >> 16;
    b->size = (data + (h->size << 2) - (char *)b - 0x20) >> 2;
    h->size = newsz;
    if ((unsigned char *)((h->p2 << 16 | h->p1 << 8 | h->p0) << 2) == rootPtn) {
        D_00040640[0] += size;
        D_00040640[0] -= (*(unsigned int *)b & 0xFFFFFF) + (*(unsigned int *)h & 0xFFFFFF);
    }
    x = h->r2 << 18 | h->r1 << 10 | h->r0 << 2 | h->q;
    b->q = x;
    b->r0 = x >> 2;
    b->r1 = x >> 10;
    b->r2 = x >> 18;
    ((Hdr **)p)[-1] = b;
    if (keep != 0) {
        ret = p;
        i = 0;
        while (n >> (i + 3)) {
            i++;
        }
        b->cls = i;
        b->f10 = h->f10;
        b->f14 = h->f14;
        b->off = (ptr + off - p) >> 2;
        h->used = 0;
        b->used = 1;
        func_00002050(ptr);
    } else {
        ret = ptr;
        h->used = 1;
        b->used = 0;
        h->off = ((char *)b - (char *)ret) >> 2;
        func_00002050(p);
    }
    return ret;
}
#endif
