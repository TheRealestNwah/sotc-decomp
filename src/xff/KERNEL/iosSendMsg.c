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
extern Thread *iosGetThread(void);
extern void iosSleepThread(void);
extern int WaitSema(int);
extern int SignalSema(int);
extern void iosCallBackThreadMgr(void (*)(Thread *), Thread *);
extern void func_000049C8(Thread *);

int iosSendMsg(MsgQueue *q, int msg, int wait)
{
    Thread *self;
    Thread *wake;
    Thread *t;
    int ret;
    int wr;

    wake = 0;
    self = iosGetThread();
loop:
    WaitSema(iosSystemSema);
    if (q->count < q->size) {
        ret = 0;
        q->buf[q->wr].msg = msg;
        wr = q->wr + 1;
        if (wr >= q->size)
            wr = 0;
        q->count++;
        q->wr = wr;
        if (q->recv) {
            if (wake)
                __asm__ volatile("break 0");
            wake = (Thread *)q->recv;
            q->recv = 0;
        }
    } else {
        ret = -1;
    }
    if (ret == -1 && wait == 1) {
        t = q->send;
        self->next = 0;
        if (t != 0) {
            while (t->next)
                t = t->next;
            t->next = self;
        } else {
            q->send = self;
        }
        SignalSema(iosSystemSema);
        iosSleepThread();
        if (q->buf != 0)
            goto loop;
        return ret;
    }
    if (wake)
        iosCallBackThreadMgr(func_000049C8, wake);
    SignalSema(iosSystemSema);
    return ret;
}
