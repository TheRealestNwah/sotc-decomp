/* Links are stored through a union (alias set 0), so the free-list count is
   loaded only after the link stores. */
typedef union GWork {
    struct {
        char pad0[0xA8];
        union GWork *next;
    } s;
} GWork;

typedef struct GWorkList {
    int num;
    GWork *head;
    GWork *tail;
} GWorkList;

extern GWorkList B_001499B0;

static inline int particleGWorkRemove(GWorkList *list, GWork *work)
{
    GWork *prev;
    GWork *cur;
    GWork *head;

    head = list->head;
    if (head != 0) {
        cur = head;
        prev = 0;
        do {
            if (cur == work) {
                if (prev != 0) {
                    prev->s.next = work->s.next;
                }
                if (list->head == work) {
                    list->head = work->s.next;
                }
                if (list->tail == work) {
                    list->tail = prev;
                }
                list->num--;
                return 1;
            }
            prev = cur;
            cur = cur->s.next;
        } while (cur != 0);
    }
    return 0;
}

static inline void particleGWorkAppend(GWorkList *list, GWork *work)
{
    if (work == 0) {
        return;
    }
    if (list->tail != 0) {
        list->tail->s.next = work;
    } else {
        list->head = work;
    }
    work->s.next = 0;
    list->tail = work;
    list->num++;
}

int particleGWorkPut(GWorkList *list, GWork *work)
{
    if (work != 0 && particleGWorkRemove(list, work)) {
        particleGWorkAppend(&B_001499B0, work);
        return 1;
    }
    return 0;
}
