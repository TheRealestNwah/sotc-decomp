#ifdef NONMATCHING
typedef struct Req {
    int type;
    unsigned int flags;
    char pad8[0x20];
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
extern void WaitSema(int);
extern void SignalSema(int);
extern void iosJumpRecoverPoint(const char *);

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

static inline void addReq(int idx, int type, int *result)
{
    Req *r = getSheetMgrReqEmpty();
    ReqList *q;

    q = &B_00155470[idx];
    r->type = type;
    r->flags &= ~1;
    r->result = result;
    if (result != 0)
        *result = 0xDEAD;
    r->next = 0;
    if (q->last != 0)
        q->last->next = r;
    else
        q->head = r;
    q->last = r;
}

void sheetMgrAllReqWait(int *result)
{
    WaitSema(B_00151860);
    addReq(4, 10, result);
    SignalSema(B_00151860);
}
#endif
