typedef struct {
    int a;
    int b;
    int c;
} Triple;
extern void *iosMallocAlign(void *, int, int);
extern void *memset(void *, int, unsigned int);

static Triple *func_000D42A0(void *heap)
{
    Triple *p = iosMallocAlign(heap, sizeof(Triple), 4);
    Triple zero;
    memset(&zero, 0, sizeof(Triple));
    *p = zero;
    return p;
}
