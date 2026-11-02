typedef struct {
    int x;
    int y;
    int id;
} AdpcmReq;

typedef struct {
    int a;
    int b;
    int started;
    int valid;
    AdpcmReq req;
} AdpcmEntry;

extern AdpcmReq *D_0017A010;
extern AdpcmEntry B_00183E10[];
extern int B_00183E64;
extern void func_00013AF0(void);
extern int bgmStandby(int, int, void *, void *);
extern void scrRun(void);

static inline AdpcmEntry *startEntry(AdpcmReq *req)
{
    AdpcmEntry *e;
    int i;

    for (i = 0; i < 3; i++) {
        if (B_00183E10[i].valid == 0)
            goto found;
    }
    return 0;
found:
    e = &B_00183E10[i];
    e->req = *req;
    if ((e->valid = bgmStandby(e->req.id, 0, func_00013AF0, e)) != 0)
        e->a = 1;
    return e;
}

void endingflowStartAdpcmSeq(AdpcmReq *req)
{
    D_0017A010 = req;
    B_00183E64 = -1;
    while (startEntry(D_0017A010) == 0)
        scrRun();
}
