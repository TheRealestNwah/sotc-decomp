extern void *malloc_from_root_partition(int, const char *);
extern char RO_0011A8C0[];
extern void sheetFileRead(void *, void *, int);
static void *func_000C73B8(void *file, int size)
{
    void *buffer = malloc_from_root_partition(size, RO_0011A8C0);
    sheetFileRead(file, buffer, size);
    return buffer;
}


