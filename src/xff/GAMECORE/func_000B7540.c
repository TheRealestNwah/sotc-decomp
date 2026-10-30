typedef struct Node {
    char pad0[0x54];
    int active;
    struct Node *next;
} Node;

typedef struct {
    char pad0[0x10];
    int count;
    Node *head;
    int pad18;
} Group;

typedef struct {
    int count;
    Group groups[1];
} GroupTable;

static int func_000B7540(GroupTable *table)
{
    int n = 0;
    int i;
    int j;
    Node *node;

    for (i = 0; i < table->count; i++) {
        node = table->groups[i].head;
        for (j = 0; j < table->groups[i].count; j++) {
            if (node->active)
                n++;
            node = node->next;
        }
    }
    return n;
}
