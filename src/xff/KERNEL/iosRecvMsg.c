typedef struct Thread {
    char pad[0x28];
    struct Thread *next;
} Thread;

typedef struct {
    int msg;
    int unk4;
} MsgEntry;

typedef struct {
    MsgEntry *buf;
    int size;
    int count;
    int wr;
    int unk10;
    int recv;
    Thread *send;
} MsgQueue;

extern int iosSystemSema;
extern unsigned char RO_00042628[];
extern void iosJumpRecoverPoint(void *, ...);
extern Thread *iosGetThread(void);
extern void iosSleepThread(void);
extern int WaitSema(int);
extern int SignalSema(int);
extern void iosCallBackThreadMgr(void (*)(Thread *), Thread *);
extern void func_000049C8(Thread *);
extern void D_000049E0(Thread *);

int iosRecvMsg(MsgQueue *q, int *msg, int wait)
{
    Thread *all;
    int ret;
    Thread *wake;
    int i;

    wake = 0;
    all = 0;
    if (q->recv)
        iosJumpRecoverPoint(RO_00042628);
loop:
    WaitSema(iosSystemSema);
    q->recv = (int)iosGetThread();
    if (q->buf != 0) {
        if (q->count != 0) {
            i = q->wr - q->count;
            if (i < 0)
                i = q->size + (q->wr - q->count);
            if (msg)
                *msg = q->buf[i].msg;
            q->count--;
            ret = 0;
            if (q->send) {
                wake = q->send;
                q->send = wake->next;
            }
        } else {
            ret = -1;
            if (wait == 1) {
                SignalSema(iosSystemSema);
                iosSleepThread();
                goto loop;
            }
        }
    } else {
        all = q->send;
        ret = 0;
        q->send = 0;
    }
    q->recv = 0;
    if (wake)
        iosCallBackThreadMgr(func_000049C8, q->send);
    if (all)
        iosCallBackThreadMgr(D_000049E0, all);
    SignalSema(iosSystemSema);
    return ret;
}
