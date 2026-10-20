typedef struct Ptn Ptn;
typedef struct {
    int buckets;
    int count;
    float scale;
    int mode;
    int current;
} SortList;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
SortList *CreateSortList(int bits, int mode, float range)
{
    SortList *list = iosMallocAlign(&rootPtn, sizeof(SortList), 4);
    int count = 1 << bits;
    int i;
    list->mode = mode;
    list->count = count;
    list->scale = (float)count / range;
    list->buckets = (int)iosMallocAlign(&rootPtn, count * sizeof(int), 4);
    for (i = 0; i < list->count; ++i)
        ((int *)list->buckets)[i] = 0;
    list->current = 0;
    return list;
}
