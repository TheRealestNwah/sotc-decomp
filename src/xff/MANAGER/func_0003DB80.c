typedef struct {
    char pad0[0x18];
    float scale;
    char pad1C[0x14];
    int child;
    int sibling;
    int mesh;
    char pad3C[4];
} Node;

typedef struct {
    char pad0[8];
    Node *nodes;
} Model;

typedef int (*NodeCallback)(void *, float, int, float);

extern int iosPushCurrentMatrix(void);
extern int iosSetCurrentMatrix(void *);
extern int iosPopCurrentMatrix(void);

/* Recursive motion-tree walk: per node, push the matrix, run the callback (or count a meshless node), set the node matrix, recurse into the child or call the callback in leaf mode, pop, then move to the sibling. The parameter order (cb, a, ctx, count, b) and the ctx and count register pins fix the argument setup and saved-register order. */
static void func_0003DB80(int idx, Model *model, char *mats, NodeCallback cb, float a, void *ctx_, int *count_, float b)
{
    register int *count __asm__("$17") = count_;
    register void *ctx __asm__("$20") = ctx_;
    Node *node;
    int sibling;
    int child;

    do {
        int off = idx * 0x40;

        node = (Node *)((char *)model->nodes + off);
        sibling = node->sibling;
        iosPushCurrentMatrix();
        child = node->child;
        if (node->mesh == -1 || cb(ctx, a, 0, node->scale * b) != 0)
            (*count)++;
        iosSetCurrentMatrix(mats + off);
        if (child != -1)
            func_0003DB80(child, model, mats, cb, a, ctx, count, b);
        else
            cb(ctx, a, 1, node->scale * b);
        iosPopCurrentMatrix();
        idx = sibling;
    } while (sibling != -1);
}
