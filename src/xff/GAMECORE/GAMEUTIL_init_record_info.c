extern void iosFree(void *);
extern void *iosMallocAlign(void *, int, int);

void GAMEUTIL_init_record_info(int *r, int a, int b, void *heap, int reset)
{
    if (reset == 1) {
        if (r[2] != 0)
            iosFree((void *)r[2]);
        r[2] = 0;
        r[3] = 0;
        r[0] = 0;
        r[1] = 0;
    }
    r[0] = a;
    r[1] = b;
    r[2] = (int)iosMallocAlign(heap, a * b, 16);
    r[3] = 0;
}
