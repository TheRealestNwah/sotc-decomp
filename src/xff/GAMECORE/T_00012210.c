typedef struct Node {
    char pad[0x18];
    struct Node *next;
} Node;

extern Node *D_00179FF4;
extern int D_00179FF8;
extern void iosFree(void *);

static void T_00012210(void *unused, Node *n)
{
    Node *p = D_00179FF4;
    Node *q;

    if (n == 0) {
        return;
    }
    if (p == n) {
        D_00179FF4 = p->next;
        iosFree(p);
        D_00179FF8--;
        return;
    }
    while (p != 0) {
        q = p->next;
        if (q == n) {
            p->next = q->next;
            iosFree(q);
            D_00179FF8--;
            return;
        }
        p = q;
    }
}
