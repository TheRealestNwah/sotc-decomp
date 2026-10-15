extern void *iosMallocAlign(void *, int, int);
extern void *memset(void *, int, unsigned int);

void *create_transform_matrix_set(void *heap)
{
    void *m = iosMallocAlign(heap, 0x280, 0x10);
    memset(m, 0, 0x280);
    return m;
}
