#ifdef NONMATCHING
/* 19 diffs (WaitSema/SignalSema return int): addresses of the lists go through v0/a1/a2 instead of v1, and the SignalSema arg is rematerialised */
typedef struct Req {
    int type;
    unsigned int flags;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
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
extern int SignalSema(int, int);
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

void sheetMgrNopSegmentIndex(int *result)
{
    Req *r;
    ReqList *q;
    int type = 9;

    WaitSema(B_00151860);
    r = popReq(&B_00155468);
    if (r == 0)
        iosJumpRecoverPoint("getSheetMgrReqEmpty: req over\n");
    r->flags &= ~1;
    q = &B_00155470[1];
    r->type = type;
    r->result = result;
    if (result)
        *result = 0xDEAD;
    r->next = 0;
    if (!(q->last == 0))
        q->last->next = r;
    else
        q->head = r;
    q->last = r;
    SignalSema(B_00151860, type);
}
#endif
