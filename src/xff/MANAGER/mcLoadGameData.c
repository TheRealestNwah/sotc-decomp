typedef struct {
    int busy;
    int port;
    int slot;
    char pad0C[4];
    int d;
    int c;
    char pad18[0x10];
    int e;
    int result;
} McReq;

typedef void (*McWaitFunction)(void);

extern void LoaderSysPrintf(const char *, ...);
extern int iosSendMsg(void *, void *, int);
extern McReq B_0014DB50[];
extern char B_0014DB10[];
extern McWaitFunction B_0014DBB4;
extern float D_00137708;
extern int D_0013771C;
typedef struct { int a, b; } __attribute__((aligned(8))) McPair;
extern McPair *D_0013770C;
extern McPair B_0014DB48;
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

static inline int mcReqWait(McReq *req)
{
    while (!mcReqSyncInline(req))
        B_0014DBB4();
    D_0013771C = 1;
    return req->result;
}

int mcLoadGameData(int port, int slot, int c, char *info)
{
    McReq *req = getMcReq();

    req->port = port;
    req->slot = slot;
    req->c = c;
    D_00137708 = 0;
    req->busy = 4;
    iosSendMsg(B_0014DB10, req, 1);
    if (mcReqWait(req) == 0) {
        B_0014DB48 = *(McPair *)(info + c * 0x98 + 0x118);
        D_0013770C = &B_0014DB48;
    }
    return req->result;
}
