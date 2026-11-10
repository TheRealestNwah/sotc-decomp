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
extern ShockReq *func_000070F0(void *pad, int *pattern, ShockPattern p);

#ifdef NONMATCHING
/* Parked: 7 words differ (prologue order and index register) */
static inline ShockSet *getSet(unsigned int k)
{
    if (k < D_000408F8->count)
        return D_000408F8->sets[k];
    return 0;
}
static inline int *getPat(ShockSet *set, unsigned int index)
{
    if (set != 0 && index < set->hdr->count)
        return &set->list[index];
    return 0;
}
ShockReq *Shock_Request(void *pad, unsigned int index, ShockPattern pattern)
{
    ShockSet *set;
    int *p;
    ShockReq *req;

    set = getSet((unsigned char)pattern.data[0]);
    p = getPat(set, index);    if (p == 0)
        return 0;
    req = func_000070F0(pad, p, pattern);
    if (req != 0)
        req->pattern = p;
    return req;
}
#endif
