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
/* Parked: 11 words differ (register allocation and branch layout) */
ShockReq *Shock_Request(void *pad, unsigned int index, ShockPattern pattern)
{
    ShockSet *set;
    int *p;
    ShockReq *req;

    set = 0;
    if ((unsigned char)pattern.data[0] < D_000408F8->count)
        set = D_000408F8->sets[(unsigned char)pattern.data[0]];
    p = 0;
    if (set != 0 && index < set->hdr->count)
        p = &set->list[index];
    if (p == 0)
        return 0;
    req = func_000070F0(pad, p, pattern);
    if (req != 0)
        req->pattern = p;
    return req;
}
#endif
