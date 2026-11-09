#ifdef NONMATCHING /* 23 diffs: same request-queue pattern as sheetMgrMapDataLoad (flags loaded in the bnel delay slot, mask and queue address in different registers). */
typedef struct Req {
    int type;
    unsigned int flags;
    int arg;
    int xC;
    int b;
    int d;
    int c;
    int e;
    int pad20[2];
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

void sheetMgrLoadSegmentIndex(int a, int b, int *result)
{
    Req *r;
    ReqList *q;

    WaitSema(B_00151860);
    r = getSheetMgrReqEmpty();
    r->arg = a;
    r->flags &= ~1;
    r->xC = b;
    r->type = 0;
    r->result = result;
    if (result != 0)
        *result = 0xDEAD;
    q = B_00155470;
    q += 3;
    r->next = 0;
    if (q->last != 0)
        q->last->next = r;
    else
        q->head = r;
    q->last = r;
    SignalSema(B_00151860);
}
#else
extern void sheetMgrLoadSegmentIndex(int a, int b, int *result);
#endif
