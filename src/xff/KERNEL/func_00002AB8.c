typedef struct Hdr {
    unsigned int next : 24;
    unsigned int p0 : 8;
    unsigned int size : 24;
    unsigned int p1 : 8;
    unsigned int link : 24;
    unsigned int p2 : 8;
    unsigned int prev : 24;
    unsigned int used : 1;
    unsigned int sub : 1;
    unsigned int align : 3;
    unsigned int own : 2;
    unsigned int b31 : 1;
    unsigned int x10 : 24;
    unsigned int o0 : 8;
    unsigned int x14 : 24;
    unsigned int o1 : 8;
    unsigned int ra : 24;
    unsigned int o2 : 8;
    struct Hdr *nextFree;
    int x20;
} Hdr;

typedef struct {
    Hdr *head;
    Hdr *tail;
} Bucket;

typedef struct Ptn {
    unsigned int table : 24;
    unsigned int t3 : 8;
    unsigned short tableNum;
    unsigned short pad6;
    unsigned int first : 24;
    unsigned int f3 : 8;
} Ptn;

extern unsigned char rootPtn[];
extern signed char D_00040650[];
extern void func_00001260(Hdr *, Bucket *, unsigned int, void *);
extern void *func_00001460(Ptn *, unsigned int, int, int);
extern void *memset(void *, int, unsigned int);
extern int D_00040640;
extern int B_0004F5F8;
extern Ptn *gbPtn;
extern char RO_000420B8[];
extern void iosJumpRecoverPoint(char *);
extern int WaitSema(int);
extern int SignalSema(int);

static inline int getClass(void *ptn, int sz)
{
    int c;

    if (ptn == rootPtn) {
        if (sz <= 0x400) {
            if (sz <= 0x80) {
                return D_00040650[sz];
            }
            if (sz > 0xC0) {
                if (sz > 0x100) {
                    c = (sz <= 0x200) ? 10 : 11;
                } else {
                    c = 9;
                }
            } else {
                c = 8;
            }
        } else {
            sz /= 1024;
            c = 0xC;
            if (sz & 0xFF00) {
                sz >>= 8;
                c = 0x14;
            }
            while ((sz >>= 1) != 0) {
                c++;
            }
        }
    } else {
        sz = sz / 1024 >> 1;
        c = 1;
        while (sz != 0) {
            sz >>= 1;
            c++;
        }
    }
    return c;
}

static Ptn *func_00002AB8(Ptn *parent, unsigned int size, int ra)
{
    Ptn *p;
    Bucket *tbl;
    Hdr *h;
    int sz;
    int cls;
    unsigned int l;

    size = (size + 3) & ~3;
    cls = getClass(0, size + 4);
    sz = size + 4;
    p = func_00001460(parent, cls * 8 + 0x30 + size, 4, ra);
    if (p == 0) {
        return 0;
    }
    {
        ((Hdr **)p)[-1]->sub = 1;
        tbl = (Bucket *)(p + 1);
        h = (Hdr *)&tbl[cls];
        memset(tbl, 0, cls * 8);
        p->tableNum = cls;
        p->table = (int)tbl >> 2;
        l = (int)p >> 2;
        h->p0 = l;
        h->p2 = l >> 16;
        h->p1 = l >> 8;
        h->next = sz >> 2;
        h->used = 0;
        h->prev = 0;
        h->link = 0;
        p->first = (int)h >> 2;
        func_00001260(h, tbl, cls, p);
    }
    return p;
}

static void func_00002CF8(Ptn *ptn, char *start, char *end, int garbageSize)
{
    Bucket *tbl;
    Hdr *h;
    int cls;
    int sz;
    unsigned int l;
    Ptn *r;
    char *p;
    register int ra __asm__("$31");
    int t;

    start = (char *)(((int)start + 3) & ~3);
    end = (char *)((int)end & ~3);
    sz = end - start;
    cls = getClass(ptn, sz);
    tbl = (Bucket *)start;
    h = (Hdr *)&tbl[cls];
    p = (char *)h + 0x20;
    if (end < p) {
        iosJumpRecoverPoint(RO_000420B8);
    }
    sz = end - p;
    D_00040640 = sz >> 2;
    memset(tbl, 0, cls * 8);
    ptn->table = (int)tbl >> 2;
    ptn->tableNum = cls;
    l = (int)ptn >> 2;
    h->p0 = l;
    h->p2 = l >> 16;
    h->p1 = l >> 8;
    h->next = sz >> 2;
    h->used = 0;
    h->prev = 0;
    h->link = 0;
    ptn->first = (int)h >> 2;
    func_00001260(h, tbl, cls, ptn);
    t = ra;
    WaitSema(B_0004F5F8);
    r = func_00002AB8(ptn, garbageSize, t);
    SignalSema(B_0004F5F8);
    gbPtn = r;
}
