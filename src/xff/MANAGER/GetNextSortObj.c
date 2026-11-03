#ifdef NONMATCHING
/* obj->next lands in v0 instead of v1 (the original copies it to v0 in the return delay slot). */
typedef struct SortObj {
    int pad[2];
    struct SortObj *next;
} SortObj;

typedef struct {
    int *items;
    int count;
    int unused[2];
    int current;
} SortList;

SortObj *GetNextSortObj(SortList *list, SortObj *obj)
{
    SortObj *next;
    if (obj == 0) {
        int i = 0;
        if (i < list->count) {
            list->current = 0;
            for (; i < list->count; i++) {
                list->current = i;
                if (list->items[i]) {
                    obj = (SortObj *)list->items[i];
                    break;
                }
            }
        }
        return obj;
    }
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(obj->next));
    next = obj->next;
    if (next == 0) {
        do {
            list->current++;
            if (list->current == list->count)
                return 0;
            next = (SortObj *)list->items[list->current];
        } while (next == 0);
    }
    return next;
}
#endif
