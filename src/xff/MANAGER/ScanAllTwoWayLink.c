typedef struct Link { struct Link *prev; struct Link *next; void *obj; } Link;

int ScanAllTwoWayLink(Link *l, void (*fn)(void *, void *), void *arg)
{
    Link *n;
    for (n = l->next; n != 0; n = n->next)
        fn(n->obj, arg);
    return 1;
}
