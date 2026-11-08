/* 2 words: the original stores flags before a; this order puts a first. */
#ifdef NONMATCHING
typedef struct Req {
    int type;
    unsigned int flags;
    int pad8[2];
    int a, b, c, d, e, f;
    int *result;
    struct Req *next;
} Req;

typedef struct ReqList {
    Req *head;
    Req *last;
} ReqList;

extern int B_00151860;
extern ReqList B_00155468;
extern ReqList B_00155470[];
extern int WaitSema(int);
extern int SignalSema(int);
extern int iosJumpRecoverPoint(const char *);

static inline Req *popReq(ReqList *fl)
{
    Req *r = fl->head;

    if (r != 0) {
        Req *n = r->next;
        fl->head = n;
        if (n == 0)
            fl->last = 0;
    }
    return r;
}

static inline Req *getSheetMgrReqEmpty(void)
{
    Req *r = popReq(&B_00155468);

    if (r == 0)
        iosJumpRecoverPoint("getSheetMgrReqEmpty: req over\n");
    return r;
}

void sheetMgrAdpcmIntLoad(int a, int b, int c, int d, int e, int f, int *result)
{
    Req *r;
    ReqList *q;

    WaitSema(B_00151860);
    r = getSheetMgrReqEmpty();
    r->type = 7;
    r->a = a;
    r->flags &= ~1;
    q = B_00155470;
    r->b = b;
    r->c = c;
    r->d = d;
    r->e = e;
    r->f = f;
    r->result = result;
    if (result != 0)
        *result = 0xDEAD;
    r->next = 0;
    if (q->last != 0)
        q->last->next = r;
    else
        q->head = r;
    q->last = r;
    do {
    } while (0);
    SignalSema(B_00151860);
}
#endif
