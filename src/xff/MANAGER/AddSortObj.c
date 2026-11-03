#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct SortObj {
    int pad;
    float key;
    struct SortObj *next;
    struct SortObj *prev;
} SortObj;

typedef struct {
    SortObj **items;
    int count;
    float scale;
    int mode;
} SortList;

void AddSortObj(SortList *list, SortObj *obj)
{
    int i;
    int idx;
    SortObj *cur;
    SortObj *link;

    i = obj->key * list->scale;
    if (i < list->count) {
        idx = 0;
        if (i >= 0)
            idx = i;
    } else {
        idx = list->count - 1;
    }
    i = idx;
    if (list->mode == 1)
        i = list->count - idx - 1;
    cur = list->items[i];
    if (cur == 0) {
        list->items[i] = obj;
        obj->next = 0;
        obj->prev = 0;
        return;
    }
    for (;;) {
        if ((list->mode == 0 && cur->key < obj->key) || (list->mode == 1 && obj->key < cur->key)) {
            link = cur->next;
            if (link == 0) {
                obj->next = 0;
                obj->prev = cur;
                cur->next = obj;
                return;
            }
            cur = link;
        } else {
            link = cur->prev;
            if (link == 0) {
                list->items[i] = obj;
                obj->prev = 0;
                obj->next = cur;
                cur->prev = obj;
                return;
            }
            link->next = obj;
            obj->next = cur;
            obj->prev = cur->prev;
            cur->prev = obj;
            return;
        }
    }
}
#endif
