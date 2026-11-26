/* NONMATCHING: 16 diffs. Storing f2C, f28, f24 in that order gives the
 * Original's registers for the incoming stack arguments ($v1/$a1), but
 * the f24 store is then scheduled after f2C instead of first. The first
 * left-child test in the kd-tree search is laid out with the recursive
 * call as the fallthrough; the Original falls through to the leaf
 * callback with the index shift after the $a0 move. */
#ifdef NONMATCHING
typedef unsigned int s128 __attribute__((mode(TI)));
typedef union {
    float f[4];
    s128 q;
} Vec4;

typedef struct {
    int axis;
    float split;
    int left;
    int right;
} TreeNodeA;

typedef struct {
    float split;
    unsigned int axis : 2;
    unsigned int left : 14;
    unsigned int leftLeaf : 1;
    unsigned int right : 14;
    unsigned int rightLeaf : 1;
} TreeNodeB;

typedef struct {
    char pad0[8];
    void *nodes;
    int root;
    int kind;
} Tree;

typedef struct {
    char pad0[0x1C];
    Tree *tree;
} TreeOwner;

typedef struct {
    int *p0;
    int f4;
    int layout;
    int fC;
    float scale;
    int f14;
    float rad;
    Vec4 *pos;
    int f20;
    int f24;
    int f28;
    int f2C;
    int f30;
    int f34;
} Query;

typedef void (*TreeCB)(Query *, Tree *, int);

extern void func_0009A258(Query *, Tree *, int);
extern void func_0009A508(Query *, Tree *, int);
extern void func_0009A7C0(Query *, Tree *, int);
extern void func_000ADA50(float *, Tree *, int, TreeCB, Query *);
extern void func_000ADB78(float *, Tree *, int, TreeCB, Query *);
extern void func_000ADCA8(float *, Tree *, int, TreeCB, Query *);

static inline void searchA(float *bounds, Tree *tree, int index, TreeCB callback, Query *query)
{
    TreeNodeA *node = &((TreeNodeA *)tree->nodes)[index];
    TreeCB cb2 = callback;
    Query *q2 = query;
    float extent = bounds[3];
    float value = bounds[node->axis];
    if (value <= node->split * query->scale + extent) {
        if (node->left >= 0)
            func_000ADA50(bounds, tree, (node->left << 1) >> 1, callback, query);
        else
            callback(query, tree, (node->left << 1) >> 1);
    }
    if (!(node->split * query->scale - extent <= value))
        return;
    if (node->right < 0) {
        cb2(q2, tree, (node->right << 1) >> 1);
        return;
    }
    func_000ADA50(bounds, tree, (node->right << 1) >> 1, callback, q2);
}

static inline void searchC(float *box, Tree *tree, int idx, TreeCB cb, Query *ctx)
{
    TreeNodeB *node = &((TreeNodeB *)tree->nodes)[idx];
    TreeCB cb2 = cb;
    Query *q2 = ctx;
    float r = box[3];
    float pos = box[node->axis];
    if (pos <= node->split * ctx->scale + r) {
        if (node->leftLeaf)
            cb(ctx, tree, node->left);
        else
            func_000ADCA8(box, tree, node->left, cb, ctx);
    }
    if (node->split * ctx->scale - r <= pos) {
        if (node->rightLeaf)
            cb2(q2, tree, node->right);
        else
            func_000ADCA8(box, tree, node->right, cb, q2);
    }
}

static inline void searchB(float *box, Tree *tree, int idx, TreeCB cb, Query *ctx)
{
    TreeNodeB *node = &((TreeNodeB *)tree->nodes)[idx];
    TreeCB cb2 = cb;
    Query *q2 = ctx;
    float r = box[3];
    float pos = box[node->axis];
    if (pos <= node->split * ctx->scale + r) {
        if (node->leftLeaf)
            cb(ctx, tree, node->left);
        else
            func_000ADB78(box, tree, node->left, cb, ctx);
    }
    if (node->split * ctx->scale - r <= pos) {
        if (node->rightLeaf)
            cb2(q2, tree, node->right);
        else
            func_000ADB78(box, tree, node->right, cb, q2);
    }
}

void func_0009AA70(int *p0, int unused, TreeOwner *owner, int f14, int fC, Vec4 *pos, int f20,
                   int layout, float rad, float scale, int f4, int f24, int f28, int f2C, int f30)
{
    Query query;
    union { Query q; Vec4 b; } u, *up = &u;
    Tree *tree;
    TreeCB cb;

    {
    u.q.p0 = p0;
    u.q.f4 = f4;
    u.q.layout = layout;
    u.q.fC = fC;
    u.q.scale = scale;
    u.q.f14 = f14;
    u.q.rad = rad;
    u.q.pos = pos;
    u.q.f20 = f20;
    u.q.f2C = f2C;
    u.q.f28 = f28;
    u.q.f24 = f24;
    u.q.f30 = f30;
    u.q.f34 = *p0;
    query = up->q;
    }
    tree = owner->tree;
    {
    u.b.q = pos->q;
    u.b.f[3] = rad;
    if (tree->kind != 0) {
        cb = func_0009A258;
        searchA(up->b.f, tree, tree->root, cb, &query);
    } else if (**(int **)(*(char **)((char *)query.layout + 0x184) + 0x20) >= 3) {
        cb = func_0009A508;
        searchC(up->b.f, tree, tree->root, cb, &query);
    } else {
        cb = func_0009A7C0;
        searchB(up->b.f, tree, tree->root, cb, &query);
    }
    }
}
#endif
