typedef struct TwoWayLink {
    struct TwoWayLink *next;
    struct TwoWayLink *prev;
    int object;
} TwoWayLink;

void InitTwoWayLink(TwoWayLink *link, int object)
{
    link->object = object;
    link->next = 0;
    link->prev = 0;
}
