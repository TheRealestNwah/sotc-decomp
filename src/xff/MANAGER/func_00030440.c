typedef union Span Span;
typedef union Node Node;

typedef union {
    struct {
        Node *head;
        int count;
    } s;
} List;

typedef struct {
    char pad0[0x50];
    Node *cur;
    List list;
} Owner;

union Span {
    struct {
        int used;
        unsigned int flag : 1;
        unsigned int start : 15;
        unsigned int len : 15;
        unsigned int top : 1;
        Owner *owner;
        int padC;
        Span *prev;
        Span *next;
    } s;
};

union Node {
    struct {
        Node *prev;
        Node *next;
        Span span;
    } s;
};

extern List D_00136554;

static void func_00030440(Node *node, Node *other)
{
    Span *a = &node->s.span;
    Span *b = &other->s.span;
    Owner *owner = a->s.owner;
    List *list;
    List *free;

    if (a->s.start == b->s.start) {
        if (b->s.prev != 0)
            b->s.prev->s.next = a;
        if (b->s.next != 0)
            b->s.next->s.prev = a;
        a->s.prev = b->s.prev;
        a->s.next = b->s.next;
        b->s.used = 0;
        list = &owner->list;
        free = &D_00136554;
        if (list->s.head == other)
            list->s.head = other->s.next;
        if (other->s.prev != 0)
            other->s.prev->s.next = other->s.next;
        if (other->s.next != 0)
            other->s.next->s.prev = other->s.prev;
        list->s.count--;
        if (free->s.head != 0)
            free->s.head->s.prev = other;
        other->s.prev = 0;
        other->s.next = free->s.head;
        free->s.head = other;
        free->s.count++;
    } else {
        if (b->s.prev != 0)
            b->s.prev->s.next = a;
        a->s.prev = b->s.prev;
        a->s.next = b;
        b->s.prev = a;
        b->s.start = b->s.start - a->s.start;
        b->s.len = b->s.len + a->s.start;
    }
    if (owner->cur == other)
        owner->cur = node;
}
