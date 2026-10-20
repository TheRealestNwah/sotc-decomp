typedef struct {
    int partition;
    int pc;
    union {
        unsigned int word;
        struct { unsigned char type; unsigned char mark; unsigned short flags; } bytes;
    } header;
    unsigned short first;
    unsigned short second;
    int reserved;
    int entry;
    int immediateDelete;
} Object;
extern int iosCreatePartitionWithPc(int, int, int);
extern void *iosMallocAlign(void *, int, int);
void *_isysCreateObj(void *heap, int type, int size, int extra, int entry, int alignment)
{
    /* Preserve the caller PC used to tag the allocation. */
    register void *ra __asm__("$31");
    int pc = (int)ra;
    int partition = iosCreatePartitionWithPc((int)heap, size + extra + 0x24, pc);
    Object *object;
    if (!partition) return 0;
    object = iosMallocAlign((void *)partition, size, alignment);
    if (object) {
        object->header.bytes.type = type;
        object->header.bytes.mark = 0;
        object->partition = partition;
        object->pc = pc;
        object->entry = entry;
        object->immediateDelete = 0;
        object->second = 0;
        object->first = 0;
        object->header.word &= 0xFFFF;
    }
    return object;
}
