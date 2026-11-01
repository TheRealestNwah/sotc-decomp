typedef struct {
    int busy;
    int port;
    int slot;
    char pad0C[0x20];
    int result;
} McReq;

typedef void (*McWaitFunction)(void);

extern void LoaderSysPrintf(const char *, ...);
extern int iosSendMsg(void *, void *, int);
extern McReq B_0014DB50[];
extern char B_0014DB10[];
extern McWaitFunction B_0014DBB4;
extern int D_00137708;
extern int D_0013771C;
extern char D_00140D10[];

static inline McReq *getMcReq(void)
{
    McReq *req = B_0014DB50;
    int i;

    for (i = 0; i < 2; i++, req++) {
        if (req->busy == 0)
            return req;
    }
    LoaderSysPrintf(D_00140D10);
    return 0;
}

static inline int mcReqSyncInline(McReq *req)
{
    return req->busy == 0;
}

int mcGetInfo(int port, int slot)
{
    McReq *req = getMcReq();

    req->port = port;
    req->slot = slot;
    D_00137708 = 0;
    req->busy = 1;
    iosSendMsg(B_0014DB10, req, 1);
    while (!mcReqSyncInline(req))
        B_0014DBB4();
    D_0013771C = 1;
    return req->result;
}
