typedef struct { void *buf; int n; char pad[0x14]; } MsgQueue;
extern void *memset(void *, int, unsigned int);

void iosCreateMsgQueue(MsgQueue *q, void *buf, int n)
{
    memset(q, 0, 0x1C);
    if (buf != 0 && n > 0)
        memset(buf, 0, n * 8);
    q->buf = buf;
    q->n = n;
}
