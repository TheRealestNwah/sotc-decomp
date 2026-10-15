extern void *iosMallocAlign(void *, int, int);
extern void spriteInitObject(void *, void *);

void *spriteCreateObject(void *heap, void *src)
{
    void *s = iosMallocAlign(heap, 0x50, 0x10);
    spriteInitObject(s, src);
    return s;
}
