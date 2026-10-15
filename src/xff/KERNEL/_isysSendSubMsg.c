typedef struct { int size; char *buf; int n; int wr; int rd; } SubMsg;
extern void *memcpy(void *, const void *, unsigned int);

int _isysSendSubMsg(SubMsg *q, void *src, int size)
{
    int w;
    if (q->size != size)
        return 0;
    w = q->wr + 1 < q->n ? q->wr + 1 : 0;
    if (w == q->rd)
        q->rd = w + 1 < q->n ? w + 1 : 0;
    memcpy(q->buf + q->wr * q->size, src, size);
    q->wr = w;
    return 1;
}
