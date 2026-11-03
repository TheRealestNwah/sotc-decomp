#ifdef NONMATCHING /* 41 diffs: register allocation and scheduling in the list-insert loop */
typedef struct SortObj {
    int pad;
    float z;
    struct SortObj *next;
    struct SortObj *prev;
} SortObj;

typedef struct {
    SortObj **arr;
    int count;
    float scale;
    int mode;
    int j;
} SortList;

void AddSortObj(SortList *l, SortObj *o)
{
    float z = o->z;
    int n = l->count;
    int i = z * l->scale;
    int k;
    int mode;
    int j;
    SortObj *p;

    if (i < n) {
        k = 0;
        if (i >= 0) {
            k = i;
        }
    } else {
        k = n - 1;
    }
    mode = l->mode;
    j = k;
    if (mode == 1) {
        j = n - k - 1;
    }
    p = l->arr[j];
    if (p == 0) {
        l->arr[j] = o;
        o->next = 0;
        o->prev = 0;
        return;
    }
    for (;;) {
        switch (mode) {
        case 0:
            if (p->z < z) {
                goto next;
            }
            break;
        case 1:
            if (z < p->z) {
                goto next;
            }
            break;
        }
        if (p->prev == 0) {
            l->arr[j] = o;
            o->prev = 0;
            o->next = p;
            p->prev = o;
            return;
        }
        p->prev->next = o;
        o->next = p;
        o->prev = p->prev;
        p->prev = o;
        return;
    next:
        if (p->next == 0) {
            o->next = 0;
            o->prev = p;
            p->next = o;
            return;
        }
        p = p->next;
    }
}
#endif
