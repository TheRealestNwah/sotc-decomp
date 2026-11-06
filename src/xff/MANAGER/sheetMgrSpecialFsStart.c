#ifdef NONMATCHING /* 5 diffs: gcc schedules the semaphore reload above the final q->last store */
typedef struct Req {
    int type;
    unsigned int flags;
    int arg;
    int seg;
    char pad10[4];
    int fsArg;
    int fs;
    char pad1c[0xC];
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
extern int sheetFsSrhSpecialFs(int);

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

void sheetMgrSpecialFsStart(int name, int arg, int *result)
{
    Req *r;
    ReqList *q;

    WaitSema(B_00151860);
    r = getSheetMgrReqEmpty();
    r->type = 11;
    r->flags &= ~1;
    r->fs = sheetFsSrhSpecialFs(name);
    r->fsArg = arg;
    q = B_00155470;
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
