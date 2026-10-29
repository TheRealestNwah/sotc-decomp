extern void *iosMallocAlign(int, int, int);
void *_SCRMallocAlign(int partition, int size, int alignment)
{
    return iosMallocAlign(partition, size, alignment);
}
