typedef struct { int a; int b; void *buf; int c; } RecordInfo;
extern void iosFree(void *);

void GAMEUTIL_destructor_record_info(RecordInfo *r)
{
    if (r->buf != 0)
        iosFree(r->buf);
    r->a = 0;
    r->b = 0;
    r->buf = 0;
    r->c = 0;
}
