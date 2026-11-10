typedef struct Blk {
    unsigned int size;
    int pad4[4];
    unsigned int prev;
    int pad18;
    struct Blk *next;
} Blk;
typedef struct { Blk *head; Blk *tail; } Bucket;

extern unsigned char rootPtn[];
extern signed char D_00040650[];

static inline int getClass(int sz)
{
    int c;
    if (sz <= 0x400) {
        if (sz <= 0x80) {
            return D_00040650[sz];
        }
        if (sz <= 0xC0) {
            c = 8;
        } else if (sz <= 0x100) {
            c = 9;
        } else if (sz <= 0x200) {
            c = 10;
        } else {
            c = 11;
        }
        return c;
    } else {
        int v = sz >> 10;
        if (v & 0xFF00) {
            v = sz >> 18;
            c = 0x14;
        } else {
            c = 0xC;
        }
        while ((v >>= 1) != 0) {
            c++;
        }
        return c;
    }
}

/* Parked: allocator free-list insert, control flow right but ~130 words differ
   (register allocation and block order of the size-class computation). */
#ifdef NONMATCHING
void func_00001260(Blk *b, Bucket *tbl, unsigned int n, void *ptn)
{
    int sz = (b->size & 0xFFFFFF) << 2;
    unsigned int idx;
    Bucket *bk;
    Blk *p;

    if (ptn == rootPtn) {
        idx = getClass(sz);
    } else {
        unsigned int v = (unsigned int)sz >> 11;
        idx = 1;
        while (v != 0) {
            v = (int)v >> 1;
            idx++;
        }
    }
    idx--;
    if (idx >= n) {
        idx = n - 1;
    }
    bk = &tbl[idx];
    p = bk->head;
    if (p == 0) {
        tbl[idx].head = b;
        tbl[idx].tail = b;
        b->next = 0;
        b->prev &= 0xFF000000;
        return;
    }
    while ((unsigned int)(sz >> 2) >= (p->size & 0xFFFFFF)) {
        if (p->next == 0) {
            tbl[idx].tail = b;
            p->next = b;
            b->next = 0;
            b->prev = (b->prev & 0xFF000000) | (((int)p >> 2) & 0xFFFFFF);
            return;
        }
        p = p->next;
    }
    b->prev = (b->prev & 0xFF000000) | (p->prev & 0xFFFFFF);
    if ((p->prev & 0xFFFFFF) == 0) {
        bk->head = b;
    } else {
        ((Blk *)((b->prev & 0xFFFFFF) << 2))->next = b;
    }
    b->next = p;
    p->prev = (p->prev & 0xFF000000) | (((int)b >> 2) & 0xFFFFFF);
}
#endif
