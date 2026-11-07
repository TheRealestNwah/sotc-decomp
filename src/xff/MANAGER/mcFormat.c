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
extern float B_0014DBB0;
extern char rootPtn[];
extern void func_000CF220(void);
extern int iosCreateThreadS(void *, int, void *, int, int, int);
extern void iosStartThread(int, int);
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

int mcFormat(int port, int slot)
{
    McReq *req = getMcReq();

    req->port = port;
    req->slot = slot;
    D_0013771C = 0;
    B_0014DBB0 = 17.0f;
    iosStartThread(iosCreateThreadS(func_000CF220, 0, rootPtn, 0x1000, 0x2F, 0), 0);
    {
        int busy = 7;

        D_00137708 = 0;
        req->busy = busy;
    }
    iosSendMsg(B_0014DB10, req, 1);
    while (!isDone(req))
        B_0014DBB4();
    D_0013771C = 1;
    return req->result;
}
