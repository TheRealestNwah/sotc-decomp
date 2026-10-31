typedef struct {
    int a, b, c;
} Trip;
extern void *iosMallocAlign(void *, int, int);
extern void *memset(void *, int, unsigned int);

static Trip *T_000D4578(void *heap)
{
    Trip *p = iosMallocAlign(heap, 0xC, 4);
    Trip t;

    memset(&t, 0, 0xC);
    *p = t;
    return p;
}
