#ifdef NONMATCHING /* 21 instruction diffs: gcc strength-reduces the first-object loop to a pointer walk; the original indexes arr[i] each pass */
typedef struct Obj {
    char pad[8];
    struct Obj *next;
} Obj;

typedef struct {
    Obj **arr;
    int count;
    int pad[2];
    int idx;
} SortList;

Obj *GetNextSortObj(SortList *l, Obj *cur)
{
    int i;
    int n;
    Obj *o;

    if (cur == 0) {
        n = l->count;
        i = 0;
        if (i < n) {
            l->idx = 0;
            o = l->arr[0];
            while (o == 0) {
                i++;
                if (i >= n) {
                    return cur;
                }
                l->idx = i;
                o = l->arr[i];
            }
            cur = o;
        }
        return cur;
    }
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(cur->next));
    o = cur->next;
    if (o == 0) {
        n = l->count;
        do {
            l->idx++;
            if (l->idx == n) {
                return 0;
            }
            o = l->arr[l->idx];
        } while (o == 0);
    }
    return o;
}
#endif
