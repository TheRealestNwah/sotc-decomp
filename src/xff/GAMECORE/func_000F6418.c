/* ~70 diffs, same size (92 words). Static (alabel) path-node relax: finds the node index for key t0 by summing sub-counts over the group entries (group table at B_001A03E8+0x5400, 152 bytes each), then relaxes node cost (stride 0x18) and links it into list a1. Loop body now matches word for word; remaining: the Original compares 0 < count via the sum register (slt t3), keeps sum/i/count in t3/t4/t5 (ours t5/t4/t3) and hoists the B_001A03E8 address into t6. Tried goto-found form, tbl/g split, i = sum = 0, count declared first. */
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
    int cnt;
    int sum = 0;
    int idx;
    Node *n;
    Node *head;
    Node *nodes = B_001A03E8;
    Grp *tbl = (Grp *)((char *)nodes + 0x5400);
    Grp *g = tbl + *(int *)(a0 + 0x3C50);

    if (a3 >= 0 && t0 >= 0) {
        Ent *e = g->e;
        int i;
        cnt = g->count;
        for (i = 0; i < cnt; i++, e++) {
            idx = sum + a3;
            if (t0 == e->item->key) {
                goto found;
            }
            if (e->sub != 0) {
                sum += *e->sub;
            }
        }
    }
    idx = -1;
found:
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
