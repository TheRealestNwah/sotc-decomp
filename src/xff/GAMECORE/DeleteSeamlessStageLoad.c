typedef struct { int a; int b; void *buf; } SeamlessLoad;
extern SeamlessLoad D_0017A340;
extern void iosFree(void *);

void DeleteSeamlessStageLoad(void)
{
    SeamlessLoad *s = &D_0017A340;
    if (s->buf != 0) {
        iosFree(s->buf);
        s->buf = 0;
    }
}
