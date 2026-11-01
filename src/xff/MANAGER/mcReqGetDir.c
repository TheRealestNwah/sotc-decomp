typedef struct {
    int busy;
    int port;
    int slot;
    int arg0C;
    int arg10;
    int arg14;
    int arg18;
    int arg1C;
    int arg20;
    int arg24;
    int arg28;
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

static inline int isDone(McReq *req)
{
    return req->busy == 0;
}

int mcReqGetDir(int port, int slot, int name, int a3, int a4, int a5, int a6)
{
    McReq *req = getMcReq();

    req->port = port;
    req->slot = slot;
    req->arg0C = name;
    req->arg18 = a3;
    req->arg1C = a4;
    req->arg20 = a5;
    req->arg24 = a6;
    D_00137708 = 0;
    req->busy = 10;
    iosSendMsg(B_0014DB10, req, 1);
    while (!isDone(req))
        B_0014DBB4();
    D_0013771C = 1;
    return req->result;
}
