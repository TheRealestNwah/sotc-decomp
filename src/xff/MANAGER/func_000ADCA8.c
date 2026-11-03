typedef struct {
    float split;
    unsigned int axis : 2;
    unsigned int left : 14;
    unsigned int leftLeaf : 1;
    unsigned int right : 14;
    unsigned int rightLeaf : 1;
} TreeNode;

typedef struct {
    char pad[8];
    TreeNode *nodes;
} Tree;

typedef struct {
    char pad[0x10];
    float scale;
} TreeCtx;

typedef void (*TreeCB)(TreeCtx *, Tree *, int);

static void func_000ADCA8(float *box, Tree *tree, int idx, TreeCB cb, TreeCtx *ctx)
{
    TreeNode *node;
    float r;
    float pos;

    node = &tree->nodes[idx];
    r = box[3];
    pos = box[node->axis];
    if (pos <= node->split * ctx->scale + r) {
        if (node->leftLeaf) {
            cb(ctx, tree, node->left);
        } else {
            func_000ADCA8(box, tree, node->left, cb, ctx);
        }
    }
    if (node->split * ctx->scale - r <= pos) {
        if (node->rightLeaf) {
            cb(ctx, tree, node->right);
        } else {
            func_000ADCA8(box, tree, node->right, cb, ctx);
        }
    }
}
