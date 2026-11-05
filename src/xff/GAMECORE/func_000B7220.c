typedef struct Node {
    char pad0[0x58];
    struct Node *next;
} Node;

typedef struct {
    int count;
    Node *head;
    Node *tail;
} List;

extern void func_000B5318(Node *);
extern void func_000B7360(Node *);

static inline int listRemove(List *list, Node *n)
{
    Node *p, *prev;

    if (list->head) {
        p = list->head;
        prev = 0;
        for (; p; p = p->next) {
            if (p == n) {
                if (prev)
                    prev->next = n->next;
                if (list->head == n)
                    list->head = n->next;
                if (list->tail == n)
                    list->tail = prev;
                list->count--;
                return 1;
            }
            prev = p;
        }
        return 0;
    }
    return 0;
}

static inline void listAppend(List *list, Node *n)
{
    if (n) {
        if (list->tail)
            list->tail->next = n;
        else
            list->head = n;
        n->next = 0;
        list->tail = n;
        list->count++;
    }
}

static int func_000B7220(char *w, List *list, Node *n)
{
    if (n && listRemove(list, n)) {
        func_000B5318(n);
        listAppend((List *)(w + 0x244), n);
        func_000B7360(n);
        return 1;
    }
    return 0;
}
