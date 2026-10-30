typedef struct {
    char pad0[0x30];
    int right;
    int left;
    char pad38[0x40 - 0x38];
} TreeNode;

typedef struct {
    char pad0[8];
    TreeNode *nodes;
} Tree;

typedef struct {
    char pad[0x10];
} TreeItem;

extern void func_00032940(TreeItem *, int, int, int, int, float);

static void func_0003D220(TreeItem *items, int a1, Tree *tree, int idx, int a4, int a5, float f)
{
    int right = tree->nodes[idx].right;

    if (tree->nodes[idx].left != -1)
        func_0003D220(items, a1, tree, tree->nodes[idx].left, a4, a5, f);
    if (right != -1)
        func_0003D220(items, a1, tree, right, a4, a5, f);
    func_00032940(&items[idx], a1, idx, a4, a5, f);
}
