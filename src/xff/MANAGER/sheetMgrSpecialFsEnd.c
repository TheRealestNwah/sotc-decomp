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

#ifdef NONMATCHING
static inline Req *getSheetMgrReqEmpty(void)
{
    Req *r = popReq(&B_00155468);

    if (r == 0)
        iosJumpRecoverPoint("getSheetMgrReqEmpty: req over\n");
    return r;
}

/* 15 diffs: free-list address goes through v0 and the semaphore reload is scheduled above the final q->last store */
void sheetMgrSpecialFsEnd(int fs, int *result)
{
    Req *r;
    ReqList *q;

    WaitSema(B_00151860);
    r = getSheetMgrReqEmpty();
    r->flags &= ~1;
    q = B_00155470;
    r->type = 12;
    q += 4;
    r->result = result;
    if (result != 0)
        *result = 0xDEAD;
    r->next = 0;
    if (q->last != 0)
        q->last->next = r;
    else
        q->head = r;
    q->last = r;
    SignalSema(B_00151860);
}
#endif
