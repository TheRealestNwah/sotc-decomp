typedef struct Req {
    int type;
    unsigned int flags;
    int arg;
    int seg;
    char pad10[0x18];
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
extern int sheetFsGetStageTexSegIndex(int, int);
extern int sheetFsAddStageTexSegIndex(int);

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

void sheetMgrStageTexLoad(int arg, int a, int b, int *result)
{
    int seg;

    WaitSema(B_00151860);
    seg = sheetFsGetStageTexSegIndex(a, b);
    if (sheetFsAddStageTexSegIndex(seg) == 0) {
        {
            Req *r = getSheetMgrReqEmpty();
            char *qq;
            ReqList *q;

            r->flags &= ~1;
            qq = (char *)B_00155470;
            q = (ReqList *)(qq + 16);
            r->type = 4;
            r->arg = arg;
            r->seg = seg;
            r->result = result;
            if (result != 0)
                *result = 0xDEAD;
            r->next = 0;
            if (q->last != 0) {
                q->last->next = r;
                q->last = r;
            } else {
                q->head = r;
                do {
                } while (0);
                q->last = r;
            }
        }
    } else if (result != 0) {
        *result = 0xDEAF;
    }
    SignalSema(B_00151860);
}
