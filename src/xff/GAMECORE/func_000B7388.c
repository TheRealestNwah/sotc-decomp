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
    Group groups[20];
    char pad234[4];
    Group extra;
} GroupTable;

typedef struct {
    char pad0[0x13C8];
    int found;
} SearchState;

extern SearchState B_0019B870;
extern int func_000B6A58(GroupTable *, void *, int, int);

static void func_000B7388(GroupTable *table, int key)
{
    int i;

    if (B_0019B870.found)
        return;
    if ((B_0019B870.found = func_000B6A58(table, &table->extra, 1, key)))
        return;
    for (i = table->count - 1; i >= 0; i--) {
        if (func_000B6A58(table, &table->groups[i].count, 1, key)) {
            B_0019B870.found = 1;
            return;
        }
    }
}
