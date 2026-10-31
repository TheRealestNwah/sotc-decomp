typedef struct {
    short pad0[2];
    short area;
    short next;
    short line;
    char pad0A[0xE];
} AreaLinkFA720;

typedef struct {
    char pad00[0xE];
    unsigned short kind;
} LineFA720;

extern AreaLinkFA720 B_001A03E8[];
extern int func_000FA7E0(void *w, int a, int b);
extern LineFA720 *getLineDataByAreaIdx(void *w, int b, int area);

static int func_000FA720(void *w, int x, int y, int a, int b)
{
    AreaLinkFA720 *tbl;
    int i;
    LineFA720 *l;

    tbl = B_001A03E8;

    i = func_000FA7E0(w, a, b);
    while (i != tbl[i].next) {
        l = getLineDataByAreaIdx(w, tbl[i].line, tbl[i].area);
        if (l != 0 && l->kind > 0x80) {
            return 1;
        }
        i = tbl[i].next;
    }
    return 0;
}
