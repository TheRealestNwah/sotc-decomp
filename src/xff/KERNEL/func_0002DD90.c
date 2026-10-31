typedef struct {
    int pad0;
    int *buf;
} Buffer;

extern void *memset(void *, int, unsigned int);

static void func_0002DD90(Buffer *b, int count)
{
    memset(b->buf, 0, count * 4);
}
