typedef struct {
    int *items;
    int count;
    int unused[2];
    int current;
} SortList;

void *GetFirstSortObj(SortList *list)
{
    int i = 0;
    void *found = 0;
    if (list->count > 0) {
        list->current = 0;
        for (; i < list->count; i++) {
            list->current = i;
            if (list->items[i]) {
                found = (void *)list->items[i];
                break;
            }
        }
    }
    return found;
}
