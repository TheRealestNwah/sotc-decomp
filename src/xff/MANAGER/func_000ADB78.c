typedef struct {
    float split;
    union {
        struct {
            unsigned int axis : 2;
            unsigned int left : 14;
            unsigned int leftLeaf : 1;
            unsigned int right : 14;
            unsigned int rightLeaf : 1;
        } f;
        int word;
    } u;
} CompactNode;

typedef struct {
    char unknown00[8];
    CompactNode *nodes;
} CompactTree;

typedef struct {
    char unknown00[0x10];
    float scale;
} Query;

typedef void (*TreeCallback)(Query *, CompactTree *, int);

static void func_000ADB78(float *bounds, CompactTree *tree, int index, TreeCallback callback, Query *query)
{
    CompactNode *node;
    float value;
    float extent;

    for (;;) {
        node = &tree->nodes[index];
        extent = bounds[3];
        value = bounds[node->u.f.axis];
        if (value <= node->split * query->scale + extent) {
            if (node->u.f.leftLeaf)
                callback(query, tree, node->u.f.left);
            else
                func_000ADB78(bounds, tree, node->u.f.left, callback, query);
        }
        if (!(node->split * query->scale - extent <= value))
            return;
        if (node->u.word < 0) {
            callback(query, tree, ((unsigned int)node->u.word >> 17) & 0x3FFF);
            return;
        }
        index = ((unsigned int)node->u.word >> 17) & 0x3FFF;
    }
}
