typedef struct {
    char pad0[0x10];
    int f10;
    int f14;
    int f18;
    int f1C;
    char pad20[4];
    int active;
} Item;

typedef struct Node {
    char pad0[4];
    Item *item;
    char pad8[4];
    struct Node *next;
} Node;

extern Node *D_00136274;

static void func_00030388(void)
{
    Node *node;

    for (node = D_00136274; node != 0; node = node->next) {
        Item *item = node->item;
        if (item->active != 0) {
            item->f14 = 0;
            item->f10 = 0;
            item->f1C = 0;
            item->f18 = 0;
        }
    }
}
