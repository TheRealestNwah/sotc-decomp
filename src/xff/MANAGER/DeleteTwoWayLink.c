typedef struct Link { struct Link *next; struct Link *prev; } Link;

int DeleteTwoWayLink(Link *l)
{
    if (l->prev != 0)
        l->prev->next = l->next;
    if (l->next != 0)
        l->next->prev = l->prev;
    l->next = 0;
    l->prev = 0;
    return 1;
}
