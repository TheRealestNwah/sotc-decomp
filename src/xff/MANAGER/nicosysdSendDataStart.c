typedef struct Ptn Ptn;
typedef struct { int id, b, pos; void *buf; int size; } SendBuf;
extern int D_00139EF0;
extern void *iosMallocAlign(Ptn *, int, int);

void nicosysdSendDataStart(SendBuf *b, int id, Ptn *ptn, int size)
{
    if (D_00139EF0 != 0) {
        b->size = size;
        if (size != 0)
            b->buf = iosMallocAlign(ptn, size, 16);
        b->id = id;
        b->pos = 0;
    }
}
