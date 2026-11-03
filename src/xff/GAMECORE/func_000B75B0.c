typedef struct Node { int x0; char pad[8]; int xC; char pad2[0x50 - 0x10]; short x50; short x52; char pad3[4]; struct Node *x58; } Node;
typedef struct { char pad[0x23C]; Node *x23C; } Obj;
static Node *func_000B75B0(Obj *o, int id)
{
    Node *n;
    if (id != -1) {
        for (n = o->x23C; n != 0; n = n->x58) {
            if (id == n->xC) return n;
        }
    }
    return 0;
}
static Node *func_000B7600(Obj *o, int a, int b)
{
    Node *n;
    Node *head;
    if (a != -1 && b != -1) {
        head = o->x23C;
        for (n = head; n != 0; n = n->x58) {
            if (n->x0 != 0 && a == n->x52 && b == n->x50) return n;
        }
        for (n = head; n != 0; n = n->x58) {
            if (a == n->x52 && b == n->x50) return n;
        }
    }
    return 0;
}
