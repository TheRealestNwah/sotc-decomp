typedef struct Node { int used; int a; struct Node *prev; struct Node *next; } Node;
extern Node *D_00136274;

void texDelete(char *t)
{
    Node *n;
    if (t == 0)
        return;
    n = (Node *)(*(char **)(*(char **)(t + 0x20) + 0xC) + 0x30);
    if (D_00136274 == n) {
        if (n->next != 0)
            n->next->prev = n->prev;
        D_00136274 = n->next;
    } else {
        if (n->next != 0)
            n->next->prev = n->prev;
        if (n->prev != 0)
            n->prev->next = n->next;
    }
    n->used = 0;
}
