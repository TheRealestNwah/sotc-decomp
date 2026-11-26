typedef struct {
    short data[2];
} ShockPattern;

typedef struct {
    char pad0[8];
    unsigned short count;
} ShockHdr;

typedef struct {
    ShockHdr *hdr;
    int pad4;
    int pad8;
    int *list;
} ShockSet;

typedef struct {
    unsigned int count;
    ShockSet **sets;
} ShockTable;

typedef struct {
    char pad0[0x3C];
    int *pattern;
} ShockReq;

extern ShockTable *D_000408F8;

typedef struct ShockNode {
    unsigned char kind;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    char *a;
    short s8;
    short sA;
    short sC;
    short pad0E;
    short s10;
    short s12;
    char *b;
    short s18;
    short s1A;
    short s1C;
    short pad1E;
    short s20;
    short s22;
    unsigned char c24;
    unsigned char pad25;
    unsigned char c26;
    unsigned char c27;
    int arg3;
    int arg4;
    struct ShockNode *next;
    struct ShockNode *prev;
    unsigned char port;
    char pad39[3];
    int *pattern;
} ShockNode;

typedef struct {
    ShockNode *head;
    ShockNode *(*alloc)(void *, int);
    int pad8;
    void *ctx;
} ShockPad;

#define PB(x) ((unsigned char *)&(x))
static ShockReq *func_000070F0(ShockPad *pad, int *pattern, ShockPattern p, int arg3, int arg4)
{
    unsigned char *pat = (unsigned char *)pattern;
    ShockSet *set;
    ShockNode *n;
    register char *a asm("$5");
    char *b;
    int v;
    int m;
    int c40;

    if (D_000408F8 == 0)
        return 0;
    if (pad == 0)
        return 0;
    set = D_000408F8->sets[PB(p)[0]];
    if (set == 0)
        return 0;
    n = pad->alloc(pad->ctx, arg4);
    if (n == 0)
        return 0;
    n->port = PB(p)[0];
    n->arg4 = arg4;
    n->arg3 = arg3;
    { char *t = pat[0] != 0xFF ? (char *)set->pad4 + ((int *)set->pad4)[pat[0]] : 0; a = t; }
    b = pat[1] != 0xFF ? (char *)set->pad8 + ((int *)set->pad8)[pat[1]] : 0;
    c40 = 0x40;
    n->a = a;
    n->b = b;
    m = 0xFF;
    n->kind = 0x11;
    n->b3 = c40;
    n->c24 = 0;
    n->s8 = 0;
    n->s12 = 0;
    n->s10 = 0;
    n->sC = 0;
    n->sA = 0;
    n->c26 = 0;
    n->s18 = 0;
    n->s22 = 0;
    n->s20 = 0;
    n->s1C = 0;
    n->s1A = 0;
    n->c27 = 0;
    n->b2 = m;
    n->b1 = PB(p)[1];
    v = pat[2] * PB(p)[2] / 255;
    n->b2 = v < 0x100 ? v : 0xFF;
    v = (pat[3] * PB(p)[3]) >> 6;
    n->next = 0;
    if (v >= 0x100)
        v = 0xFF;
    n->b3 = v;
    n->prev = pad->head;
    if (pad->head != 0)
        pad->head->next = n;
    pad->head = n;
    return (ShockReq *)n;
}


static inline ShockSet *getSet(unsigned int k)
{
    ShockSet *r = 0;
    if (k < D_000408F8->count) {
        __asm__ __volatile__("");
        r = D_000408F8->sets[k];
    }
    return r;
}
static inline int *getPat(ShockSet *set, unsigned int index)
{
    if (set != 0 && index < set->hdr->count)
        return &set->list[index];
    return 0;
}
ShockReq *Shock_Request(void *pad, unsigned int index, ShockPattern pattern, int arg3, int arg4)
{
    ShockSet *set;
    int *p;
    ShockReq *req;

    set = getSet((unsigned char)pattern.data[0]);
    p = getPat(set, index);
    if (p == 0)
        return 0;
    req = func_000070F0(pad, p, pattern, arg3, arg4);
    if (req != 0)
        req->pattern = p;
    return req;
}
