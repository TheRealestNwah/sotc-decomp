typedef struct {
    int axis;
    float split;
    int left;
    int right;
} TreeNode;

typedef struct {
    char unknown00[8];
    TreeNode *nodes;
} Tree;

typedef struct {
    char unknown00[0x10];
    float scale;
} Query;

typedef void (*TreeCallback)(Query *, Tree *, int);

static void func_000ADA50(float *bounds, Tree *tree, int index, TreeCallback callback, Query *query)
{
    TreeNode *node;
    float value;
    float extent;

    for (;;) {
        node = &tree->nodes[index];
        extent = bounds[3];
        value = bounds[node->axis];
        if (value <= node->split * query->scale + extent) {
            if (node->left < 0)
                callback(query, tree, (node->left << 1) >> 1);
            else
                func_000ADA50(bounds, tree, (node->left << 1) >> 1, callback, query);
        }
        if (!(node->split * query->scale - extent <= value))
            return;
        if (node->right < 0) {
            callback(query, tree, (node->right << 1) >> 1);
            return;
        }
        index = (node->right << 1) >> 1;
    }
}
