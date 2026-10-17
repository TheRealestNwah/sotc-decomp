typedef struct {
    int type;
    int unused[2];
} Node;

typedef struct {
    char pad[16];
    Node *nodes;
    int count;
} Root;

int IsLwsOrientRootNode(Root *root)
{
    Node *nodes;
    int i;
    int found = 0;
    int *type;
    for (i = 0; i < root->count; i++) {
        nodes = root->nodes;
        type = &nodes[i].type;
        if (*type == 14) {
            found = 1;
            break;
        }
    }
    return found;
}
