/* ~80 diffs, same size (92 words). Static (alabel) path-node relax: looks up the node index for key t0 by summing sub-counts over the group entries (group at B_001A03E8+0x5400, 152 bytes each), then relaxes node cost (stride 0x18) and links it into list a1. Structure and data layout are right; the Original hoists the B_001A03E8 address into t6 and the zero constant shared by sum and i, so register allocation and scheduling differ throughout. */
typedef struct Node {
    char pad0[6];
    short s6;
    short s8;
    short sA;
    float cost;
    struct Node *next;
    struct Node *prev;
} Node;
typedef struct { Node *head; int count; } NodeList;
typedef struct { int pad[7]; int key; } Item;
typedef struct { Item *item; int *sub; char pad[0x1C]; } Ent;
typedef struct { Ent e[4]; int count; char pad[0x8]; } Grp;
extern Node B_001A03E8[];

#ifdef NONMATCHING
void func_000F6418(char *a0, NodeList *list, int a2, int a3, int t0, int t1, float f)
{
    int sum = 0;
    int idx;
    Node *n;
    Node *head;
    Node *nodes = B_001A03E8;
    Grp *g = (Grp *)((char *)nodes + 0x5400) + *(int *)(a0 + 0x3C50);

    idx = -1;
    if (a3 >= 0 && t0 >= 0) {
        Ent *e = g->e;
        int n = g->count;
        int i;
        for (i = 0; i < n; i++, e++) {
            if (t0 == e->item->key) {
                idx = sum + a3;
                break;
            }
            if (e->sub != 0) {
                sum += *e->sub;
            }
        }
    }
    if (idx == -1) {
        return;
    }
    n = &nodes[idx];
    if (n->sA == 0) {
        return;
    }
    if (n->s6 == -1) {
        n->s6 = a2;
        n->s8 = t1;
        n->cost = nodes[a2].cost + f;
        head = list->head;
        if (head == 0) {
            list->head = n;
            n->next = 0;
            list->head->prev = 0;
        } else {
            head->next = n;
            list->head = n;
            n->next = 0;
            list->head->prev = head;
        }
        list->count++;
    } else {
        f = nodes[a2].cost + f;
        if (nodes[a2].s6 != idx && f < n->cost) {
            n->s8 = t1;
            n->s6 = a2;
            n->cost = f;
        }
    }
}
#endif
