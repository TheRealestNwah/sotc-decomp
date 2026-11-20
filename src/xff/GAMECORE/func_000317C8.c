/* Parked attempt: 6 words differ from the Original. */
#ifdef NONMATCHING
typedef struct ArrowNode {
    char pad0[0x90];
    void *obj90;
    void *obj94;
    char pad98[4];
    int f9C;
    char padA0[8];
    short fA8;
    char padAA[0x16];
    struct ArrowNode *next;
} ArrowNode;

typedef struct {
    int count;
    ArrowNode *head;
    ArrowNode *tail;
} ArrowList;

extern ArrowList B_00189DF0;
extern ArrowList B_00189DFC;
extern void isysRequestDeleteObj(void *);
extern void EndArrowWater(void *);

static inline int arrowListRemove(ArrowList *l, ArrowNode *n)
{
    ArrowNode *p;
    ArrowNode *prev;

    if (l->head == 0)
        return 0;
    prev = 0;
    for (p = l->head; p != 0; p = p->next) {
        if (p == n) {
            if (prev != 0)
                prev->next = n->next;
            if (l->head == n)
                l->head = n->next;
            if (l->tail == n)
                l->tail = prev;
            l->count--;
            return 1;
        }
        prev = p;
    }
    return 0;
}

static inline void arrowListAppend(ArrowList *l, ArrowNode *n)
{
    if (n != 0) {
        if (l->tail != 0)
            l->tail->next = n;
        else
            l->head = n;
        *(int *)&n->next = 0;
        l->tail = n;
        l->count++;
    }
}

static void func_000317C8(ArrowNode *n)
{
    if (n->obj90 != 0 && n->f9C == 0)
        isysRequestDeleteObj(n->obj90);
    n->obj90 = 0;
    n->f9C = 0;
    if (n->fA8 != 0)
        EndArrowWater(n->obj94);
    isysRequestDeleteObj(n->obj94);
    if (n != 0 && arrowListRemove(&B_00189DF0, n)) {
        arrowListAppend(&B_00189DFC, n);
        n->obj94 = 0;
    }
}
#endif
