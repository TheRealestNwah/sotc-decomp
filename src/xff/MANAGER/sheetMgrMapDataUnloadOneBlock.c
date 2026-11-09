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

void sheetMgrMapDataUnloadOneBlock(int a, int b, int c, int *result)
{
    Req *r;
    char *qq;
    ReqList *q;

    WaitSema(B_00151860);
    r = getSheetMgrReqEmpty();
    r->flags &= ~1;
    qq = (char *)B_00155470;
    q = (ReqList *)(qq + 8);
    r->type = 3;
    r->arg = c;
    r->b = a;
    r->d = b;
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
