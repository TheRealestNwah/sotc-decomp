typedef struct Link { struct Link *prev; struct Link *next; void *obj; } Link;

int DeleteAllTwoWayLink(Link *l, void (*fn)(void *))
{
    Link *n = l->next;
    Link *next;
    while (n != 0) {
        next = n->next;
        n->prev = 0;
        n->next = 0;
        if (fn != 0)
            fn(n->obj);
        n = next;
    }
    l->next = 0;
    return 1;
}
