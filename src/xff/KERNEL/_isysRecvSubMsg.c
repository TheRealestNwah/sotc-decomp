typedef struct { int size; char *buf; int n; int wr; int rd; } SubMsg;
extern void *memcpy(void *, const void *, unsigned int);

int _isysRecvSubMsg(SubMsg *q, void *dst, int size)
{
    int r;
    if (q->size != size)
        return 0;
    if (q->rd == q->wr)
        return 0;
    memcpy(dst, q->buf + q->rd * q->size, size);
    r = q->rd + 1;
    if (r >= q->n)
        r = 0;
    q->rd = r;
    return 1;
}
