extern void *g_pLetterMem;
extern void *iosMallocAlign(void *, int, int);
extern void func_0001BFE8(void *);

void *create_letter_post(void)
{
    void *p = iosMallocAlign(g_pLetterMem, 0x14, 0x10);
    func_0001BFE8(p);
    return p;
}
