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

extern char B_0004E5B0[];
extern int iosSendMsg(MsgQueue *, int, int);
int iosWaitIdleThread(void)
{
    return iosSendMsg((MsgQueue *)B_0004E5B0, 0, 1);
}
